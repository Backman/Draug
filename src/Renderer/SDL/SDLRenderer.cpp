#include "SDLRenderer.h"
#include "Core/Window/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Log/Log.h"
#include <SDL/SDL.h>
#include <SDL/SDL_render.h>
#include <SDL/SDL_image.h>

namespace Draug {
void SDLRenderer::init(const RendererConfig& config) {
	m_window = static_cast<SDL_Window*>(config.window->getNativeWindow());

	uint32 flags = 0;
	m_renderer = SDL_CreateRenderer(m_window, -1, flags);
	if (m_renderer == nullptr) {
		DRAUG_CORE_ERROR("Failed to create SDL renderer: {0}", IMG_GetError());
		return;
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	uint32 img_flags = IMG_InitFlags::IMG_INIT_JPG;
	if (IMG_Init(img_flags) == 0) {
		DRAUG_CORE_ERROR("Failed to init SDL image: {0}", IMG_GetError());
	}
}

void SDLRenderer::shutdown() {
	if (m_renderer != nullptr) {
		SDL_DestroyRenderer(m_renderer);
	}
}

void SDLRenderer::render() {
}

void SDLRenderer::beginPass() {
	SDL_RenderClear(m_renderer);
}

void SDLRenderer::endPass() {
	SDL_RenderPresent(m_renderer);
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
	SDL_RenderCopy(m_renderer, texture.texture, NULL, &rect);
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
	SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(m_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	if (sdl_texture == nullptr) {
		DRAUG_CORE_ERROR("Failed to create texture: {0}", IMG_GetError());
		return texture;
	}
	texture->texture = sdl_texture;
	texture->data = tex_data;
	return texture;
}
}
