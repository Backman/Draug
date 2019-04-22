#include "SDLRenderer.h"
#include "Core/Window/Window.h"
#include "Core/Window/SDL/SDLWindow.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Log/Log.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

namespace Draug {
void SDLRenderer::init(const RendererConfig& config) {
	Window* window = config.window;
	m_window = static_cast<SDL_Window*>(window->getNativeWindow());
	m_context = SDL_GL_CreateContext(m_window);
	if (m_context == nullptr) {
		DRAUG_CORE_ERROR("Failed to create create GL context: {0}", IMG_GetError());
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	int32 gl_version_major;
	int32 gl_version_minor;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_version_major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_version_minor);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, window->getWidth(), window->getHeight());
	glColor4f(1.0, 1.0, 1.0, 1.0);

	DRAUG_CORE_DEBUG("OpenGL Version - Major: {0}, Minor: {1}", gl_version_major, gl_version_minor);

	DRAUG_CORE_DEBUG("OpenGL renderer: {0}", glGetString(GL_RENDERER));
	DRAUG_CORE_DEBUG("OpenGL version supported: {0}", glGetString(GL_VERSION));

	uint32 img_flags = IMG_InitFlags::IMG_INIT_JPG;
	if (IMG_Init(img_flags) == 0) {
		DRAUG_CORE_ERROR("Failed to init SDL image: {0}", IMG_GetError());
	}
}

void SDLRenderer::shutdown() {
	if (m_context != nullptr) {
		SDL_GL_DeleteContext(m_context);
	}
}

void SDLRenderer::beginPass() {
	glClear(GL_COLOR_BUFFER_BIT);	
}

void SDLRenderer::render() {
	glRotated(0.03, 0.0f, 0.0f, 1);
	glRectf(-.75, .75, .75, -.75);
}

void SDLRenderer::endPass() {
	SDL_GL_SwapWindow(m_window);
}

void SDLRenderer::draw(const Texture& texture, const int32 x_pos, const int32 y_pos) {
	if (texture.texture == nullptr) {
		return;
	}
	SDL_Rect rect;
	rect.x = x_pos;
	rect.y = y_pos;
	rect.w = texture.data.width;
	rect.h = texture.data.height;
}

Texture* SDLRenderer::createTexture(const std::string& path, const TextureData& data) {
	Texture* texture = new Texture();
	SDL_Surface* tmp_surface = IMG_Load(path.c_str());
	if (tmp_surface == nullptr) {
		DRAUG_CORE_ERROR("Failed to load texture: {0}", IMG_GetError());
		return texture;
	}
	TextureData tex_data(data);
	if (data.width == 0) {
		tex_data.width = tmp_surface->w;
	}
	if (data.height == 0) {
		tex_data.height = tmp_surface->h;
	}
	return texture;
	//SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(m_renderer, tmp_surface);
	//SDL_FreeSurface(tmp_surface);
	//if (sdl_texture == nullptr) {
	//	DRAUG_CORE_ERROR("Failed to create texture: {0}", IMG_GetError());
	//	return texture;
	//}
	//texture->texture = sdl_texture;
	//texture->data = tex_data;
	//return texture;
}
}
