#include "ImGui.h"
#include "Input/Input.h"

#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>
#include <bx/allocator.h>
#include <bx/math.h>
#include <bx/timer.h>
#include <dear-imgui/imgui.h>

#include <GLFW/glfw3.h>

#include "Shaders/vs_ocornut_imgui.bin.h"
#include "Shaders/fs_ocornut_imgui.bin.h"
#include "Shaders/vs_imgui_image.bin.h"
#include "Shaders/fs_imgui_image.bin.h"

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_ocornut_imgui),
	BGFX_EMBEDDED_SHADER(fs_ocornut_imgui),
	BGFX_EMBEDDED_SHADER(vs_imgui_image),
	BGFX_EMBEDDED_SHADER(fs_imgui_image),

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

		if (NULL == _allocator) {
			static bx::DefaultAllocator allocator;
			m_allocator = &allocator;
		}

		m_view_id = 255;
		m_last_scroll = 0;
		m_last = bx::getHPCounter();

		ImGui::SetAllocatorFunctions(mem_alloc, mem_free, NULL);

		m_imgui = ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(1280.0f, 720.0f);
		io.DeltaTime = 1.0f / 60.0f;
		io.IniFilename = NULL;

		setup_style(true);


		unsigned char* data;
		int width, height;
		// Setup vertex declaration
		m_vert_decl
			.begin()
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();

		// Create font
		io.Fonts->AddFontDefault();
		io.Fonts->GetTexDataAsRGBA32(&data, &width, &height);
		m_font_texture = bgfx::createTexture2D((uint16_t)width, (uint16_t)height, false, 1, bgfx::TextureFormat::BGRA8, 0, bgfx::copy(data, width * height * 4));
		m_font_uniform = bgfx::createUniform("s_tex", bgfx::UniformType::Sampler);

		// Create shader program
		bgfx::RendererType::Enum type = bgfx::getRendererType();
		m_program = bgfx::createProgram(
			bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_ocornut_imgui"),
			bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_ocornut_imgui"),
			true);

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
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

		bgfx::destroy(m_font_uniform);
		bgfx::destroy(m_font_texture);

		//bgfx::destroy(u_imageLodEnabled);
		//bgfx::destroy(m_imageProgram);
		bgfx::destroy(m_program);

		m_allocator = NULL;
	}

	void begin_frame(int width, int height, bgfx::ViewId view_id) {
		m_view_id = view_id;

		ImGuiIO& io = ImGui::GetIO();
		//if (_inputChar >= 0) {
		//	io.AddInputCharacter(_inputChar);
		//}

		io.DisplaySize = ImVec2((float)width, (float)height);

		const int64_t now = bx::getHPCounter();
		const int64_t frame_time = now - m_last;
		m_last = now;
		const double freq = double(bx::getHPFrequency());
		io.DeltaTime = float(frame_time / freq);

		int scroll = Draug::Input::Input::mouse.y_scroll();

		io.MousePos = ImVec2((float)Draug::Input::Input::mouse.x_pos(), (float)Draug::Input::Input::mouse.y_pos());
		io.MouseDown[0] = Draug::Input::Input::mouse.is_button_pressed(Draug::Input::MouseButton::Left);
		io.MouseDown[1] = Draug::Input::Input::mouse.is_button_pressed(Draug::Input::MouseButton::Right);
		io.MouseDown[2] = Draug::Input::Input::mouse.is_button_pressed(Draug::Input::MouseButton::Middle);
		io.MouseWheel = (float)(scroll - m_last_scroll);
		m_last_scroll = scroll;

		io.KeyShift = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::LeftShift) || Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::RightShift);
		io.KeyCtrl = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::LeftControl) || Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::RightControl);
		io.KeyAlt = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::LeftAlt) || Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::RightAlt);
		io.KeySuper = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::LeftSuper) || Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::RightSuper);
		for (int32_t ii = 0; ii < (int32_t)Draug::Input::Key::Count; ++ii) {
			io.KeysDown[ii] = Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::Code(ii));
		}

		ImGui::NewFrame();
	}

	void end_frame() {
		ImGui::Render();
		render(ImGui::GetDrawData());
	}

	void render(ImDrawData* draw_data) {
		const ImGuiIO& io = ImGui::GetIO();
		const float width = io.DisplaySize.x;
		const float height = io.DisplaySize.y;

		bgfx::setViewName(m_view_id, "ImGui");
		bgfx::setViewMode(m_view_id, bgfx::ViewMode::Sequential);

		const bgfx::Caps* caps = bgfx::getCaps();
		{
			float ortho[16];
			bx::mtxOrtho(ortho, 0.0f, width, height, 0.0f, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
			bgfx::setViewTransform(m_view_id, NULL, ortho);
			bgfx::setViewRect(m_view_id, 0, 0, uint16_t(width), uint16_t(height));
		}

		// Render command lists
		for (int32_t ii = 0, num = draw_data->CmdListsCount; ii < num; ++ii) {
			bgfx::TransientVertexBuffer tvb;
			bgfx::TransientIndexBuffer tib;

			const ImDrawList* drawList = draw_data->CmdLists[ii];
			uint32_t numVertices = (uint32_t)drawList->VtxBuffer.size();
			uint32_t numIndices = (uint32_t)drawList->IdxBuffer.size();

			if (!check_available_transient_buffers(numVertices, m_vert_decl, numIndices)) {
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
					uint64_t state = 0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_MSAA
						;

					bgfx::TextureHandle th = m_font_texture;
					bgfx::ProgramHandle program = m_program;

					if (NULL != cmd->TextureId) {
						union { ImTextureID ptr; struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; } texture = { cmd->TextureId };
						state |= 0 != (IMGUI_FLAGS_ALPHA_BLEND & texture.s.flags)
							? BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
							: BGFX_STATE_NONE
							;
						th = texture.s.handle;
					}
					else {
						state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
					}

					const uint16_t xx = uint16_t(bx::max(cmd->ClipRect.x, 0.0f));
					const uint16_t yy = uint16_t(bx::max(cmd->ClipRect.y, 0.0f));
					bgfx::setScissor(xx, yy, uint16_t(bx::min(cmd->ClipRect.z, 65535.0f) - xx), uint16_t(bx::min(cmd->ClipRect.w, 65535.0f) - yy));

					bgfx::setState(state);
					bgfx::setTexture(0, m_font_uniform, th);
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
	bgfx::UniformHandle m_font_uniform;
	int64_t m_last;
	int32_t m_last_scroll;
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

void imgui_begin_frame(int width, int height, bgfx::ViewId view_id) {
	s_ctx.begin_frame(width, height, view_id);
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
