#include "ImGui.h"
#include "Input/Input.h"

#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>
#include <bx/allocator.h>
#include <bx/math.h>
#include <bx/timer.h>
#include <dear-imgui/imgui.h>

#include <GLFW/glfw3.h>

#include "Shaders/vs_imgui.bin.h"
#include "Shaders/fs_imgui.bin.h"

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_imgui),
	BGFX_EMBEDDED_SHADER(fs_imgui),

	BGFX_EMBEDDED_SHADER_END()
};

namespace Draug {
const char* imgui_get_clipboard_text(void* userData);
void imgui_set_clipboard_text(void* userData, const char* text);

static void* mem_alloc(size_t size, void* user_data);
static void mem_free(void* ptr, void* user_data);

bool check_available_transient_buffers(uint32_t _numVertices, const bgfx::VertexDecl& _decl, uint32_t _numIndices) {
	return _numVertices == bgfx::getAvailTransientVertexBuffer(_numVertices, _decl)
		&& (0 == _numIndices || _numIndices == bgfx::getAvailTransientIndexBuffer(_numIndices))
		;
}

struct ImguiContext {
	void create(float font_size, bx::AllocatorI* _allocator) {
		m_allocator = _allocator;

		if (_allocator == nullptr) {
			static bx::DefaultAllocator allocator;
			m_allocator = &allocator;
		}

		m_view_id = 255;
		m_last = bx::getHPCounter();

		ImGui::SetAllocatorFunctions(mem_alloc, mem_free, nullptr);

		m_imgui = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(1280.0f, 720.0f);
		io.DeltaTime = 1.0f / 60.0f;
		io.IniFilename = nullptr;

		setup_style(true);

		// Setup vertex declaration
		m_vert_decl
			.begin()
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();

		unsigned char* font_data;
		int32_t font_width, font_height;
		ImFontConfig font_config = ImFontConfig();
		font_config.SizePixels = font_size;
		io.Fonts->AddFontDefault(&font_config);
		io.Fonts->GetTexDataAsRGBA32(&font_data, &font_width, &font_height);
		m_font_texture = bgfx::createTexture2D((uint16_t)font_width, (uint16_t)font_height,
			false, 1, bgfx::TextureFormat::BGRA8, 0, bgfx::copy(font_data, font_width * font_height * 4));
		u_font_texture = bgfx::createUniform("s_tex", bgfx::UniformType::Sampler);

		// Create shader program
		bgfx::RendererType::Enum type = bgfx::getRendererType();
		m_program = bgfx::createProgram(
			bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui"),
			bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui"),
			true);

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors
			| ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard
			| ImGuiConfigFlags_DockingEnable;

		io.BackendPlatformName = "draug_imgui";

		io.KeyMap[ImGuiKey_Tab] = Draug::Input::Key::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = Draug::Input::Key::Left;
		io.KeyMap[ImGuiKey_RightArrow] = Draug::Input::Key::Right;
		io.KeyMap[ImGuiKey_UpArrow] = Draug::Input::Key::Up;
		io.KeyMap[ImGuiKey_DownArrow] = Draug::Input::Key::Down;
		io.KeyMap[ImGuiKey_PageUp] = Draug::Input::Key::PageUp;
		io.KeyMap[ImGuiKey_PageDown] = Draug::Input::Key::PageDown;
		io.KeyMap[ImGuiKey_Home] = Draug::Input::Key::Home;
		io.KeyMap[ImGuiKey_End] = Draug::Input::Key::End;
		io.KeyMap[ImGuiKey_Insert] = Draug::Input::Key::Insert;
		io.KeyMap[ImGuiKey_Delete] = Draug::Input::Key::Delete;
		io.KeyMap[ImGuiKey_Backspace] = Draug::Input::Key::BackSpace;
		io.KeyMap[ImGuiKey_Space] = Draug::Input::Key::Space;
		io.KeyMap[ImGuiKey_Enter] = Draug::Input::Key::Enter;
		io.KeyMap[ImGuiKey_Escape] = Draug::Input::Key::Escape;
		io.KeyMap[ImGuiKey_A] = Draug::Input::Key::A;
		io.KeyMap[ImGuiKey_C] = Draug::Input::Key::C;
		io.KeyMap[ImGuiKey_V] = Draug::Input::Key::V;
		io.KeyMap[ImGuiKey_X] = Draug::Input::Key::X;
		io.KeyMap[ImGuiKey_Y] = Draug::Input::Key::Y;
		io.KeyMap[ImGuiKey_Z] = Draug::Input::Key::Z;
		io.GetClipboardTextFn = imgui_get_clipboard_text;
		io.SetClipboardTextFn = imgui_set_clipboard_text;
	}

	void destroy() {
		ImGui::DestroyContext(m_imgui);

		bgfx::destroy(u_font_texture);
		bgfx::destroy(m_font_texture);
		bgfx::destroy(m_program);

		m_allocator = NULL;
	}

	void begin_frame(Window* window) {
		m_view_id = window->get_id();

		ImGuiIO& io = ImGui::GetIO();
		//if (_inputChar >= 0) {
		//	io.AddInputCharacter(_inputChar);
		//}

		int w = window->get_width();
		int h = window->get_height();
		int dw = window->get_framebuffer_width();
		int dh = window->get_framebuffer_height();

		io.DisplaySize = ImVec2((float)w, (float)h);
		io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)dw / w) : 0, h > 0 ? ((float)dh / h) : 0);

		const int64_t now = bx::getHPCounter();
		const int64_t frame_time = now - m_last;
		m_last = now;
		const double freq = double(bx::getHPFrequency());
		io.DeltaTime = float(frame_time / freq);

		float scroll = Draug::Input::Input::mouse.y_scroll();

		io.MousePos = ImVec2((float)Draug::Input::Input::mouse.x_pos(), (float)Draug::Input::Input::mouse.y_pos());
		io.MouseDown[0] = Draug::Input::Input::mouse.is_button_pressed(Draug::Input::MouseButton::Left);
		io.MouseDown[1] = Draug::Input::Input::mouse.is_button_pressed(Draug::Input::MouseButton::Right);
		io.MouseDown[2] = Draug::Input::Input::mouse.is_button_pressed(Draug::Input::MouseButton::Middle);
		io.MouseWheel = (float)scroll;

		io.KeyShift = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::LeftShift) || Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::RightShift);
		io.KeyCtrl = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::LeftControl) || Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::RightControl);
		io.KeyAlt = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::LeftAlt) || Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::RightAlt);
		io.KeySuper = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::LeftSuper) || Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::RightSuper);
		for (int32_t ii = 0; ii < (int32_t)Draug::Input::Key::Count; ++ii) {
			io.KeysDown[ii] = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::Code(ii));
		}

//#ifdef _WIN32
//		io.ImeWindowHandle = window->get_native_window_ptr();
//#endif

		ImGui::NewFrame();
	}

	void end_frame() {
		ImGui::Render();
		render(ImGui::GetDrawData());
	}

	void render(ImDrawData* draw_data) {
		for (int32_t ii = 0, num = draw_data->CmdListsCount; ii < num; ++ii) {
			bgfx::TransientVertexBuffer tvb;
			bgfx::TransientIndexBuffer tib;

			const ImDrawList* drawList = draw_data->CmdLists[ii];
			uint32_t numVertices = (uint32_t)drawList->VtxBuffer.size();
			uint32_t numIndices = (uint32_t)drawList->IdxBuffer.size();

			if (bgfx::getAvailTransientVertexBuffer(numVertices, m_vert_decl) == false || bgfx::getAvailTransientIndexBuffer(numIndices) == false) {
				// not enough space in transient buffer just quit drawing the rest...
				break;
			}

			bgfx::allocTransientVertexBuffer(&tvb, numVertices, m_vert_decl);
			bgfx::allocTransientIndexBuffer(&tib, numIndices);

			ImDrawVert* verts = (ImDrawVert*)tvb.data;
			bx::memCopy(verts, drawList->VtxBuffer.begin(), numVertices * sizeof(ImDrawVert));

			ImDrawIdx* indices = (ImDrawIdx*)tib.data;
			bx::memCopy(indices, drawList->IdxBuffer.begin(), numIndices * sizeof(ImDrawIdx));

			uint32_t offset = 0;
			for (const ImDrawCmd* cmd = drawList->CmdBuffer.begin(), *cmdEnd = drawList->CmdBuffer.end(); cmd != cmdEnd; ++cmd) {
				if (cmd->UserCallback) {
					cmd->UserCallback(drawList, cmd);
				}
				else if (0 != cmd->ElemCount) {
					uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA;

					bgfx::TextureHandle th = m_font_texture;
					bgfx::ProgramHandle program = m_program;

					if (cmd->TextureId != NULL) {
						th.idx = uint16_t(uintptr_t(cmd->TextureId));
					}
					state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);

					const uint16_t xx = uint16_t(bx::max(cmd->ClipRect.x, 0.0f));
					const uint16_t yy = uint16_t(bx::max(cmd->ClipRect.y, 0.0f));
					bgfx::setScissor(xx, yy, uint16_t(bx::min(cmd->ClipRect.z, 65535.0f) - xx), uint16_t(bx::min(cmd->ClipRect.w, 65535.0f) - yy));
					bgfx::setState(state);
					bgfx::setTexture(0, u_font_texture, th);
					bgfx::setVertexBuffer(0, &tvb, 0, numVertices);
					bgfx::setIndexBuffer(&tib, offset, cmd->ElemCount);
					bgfx::submit(m_view_id, program);
				}

				offset += cmd->ElemCount;
			}
		}
	}

	void setup_style(bool dark) {
		// Doug Binks' darl color scheme
		// https://gist.github.com/dougbinks/8089b4bbaccaaf6fa204236978d165a9
		ImGuiStyle& style = ImGui::GetStyle();
		if (dark) {
			ImGui::StyleColorsDark(&style);
		}
		else {
			ImGui::StyleColorsLight(&style);
		}

		style.FrameRounding = 4.0f;
		style.WindowBorderSize = 0.0f;
	}

	ImGuiContext* m_imgui;
	bx::AllocatorI* m_allocator;
	bgfx::VertexDecl m_vert_decl;
	bgfx::ProgramHandle m_program;
	bgfx::TextureHandle m_font_texture;
	bgfx::UniformHandle u_font_texture;
	int64_t m_last;
	bgfx::ViewId m_view_id;
};

static ImguiContext s_ctx;

static void* mem_alloc(size_t size, void* user_data) {
	BX_UNUSED(user_data);
	return BX_ALLOC(s_ctx.m_allocator, size);
}

static void mem_free(void* ptr, void* user_data) {
	BX_UNUSED(user_data);
	BX_FREE(s_ctx.m_allocator, ptr);
}

void imgui_init(float font_size, bx::AllocatorI* allocator) {
	s_ctx.create(font_size, allocator);
}

void imgui_begin_frame(Window* window) {
	s_ctx.begin_frame(window);
}

void imgui_end_frame() {
	s_ctx.end_frame();
}

void imgui_shutdown() {
	s_ctx.destroy();
}

static const char* imgui_get_clipboard_text(void* userData) {
	return glfwGetClipboardString((GLFWwindow*)userData);
}

static void imgui_set_clipboard_text(void* userData, const char* text) {
	glfwSetClipboardString((GLFWwindow*)userData, text);
}
}
