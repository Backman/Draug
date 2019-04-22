#include "Renderer.h"
#include "Texture.h"
#include "Core/Window/Window.h"

namespace Draug {
RendererImpl Renderer::m_impl;

void Renderer::init(const RendererConfig& config) {
	m_impl.init(config);
}

void Renderer::shutdown() {
	m_impl.shutdown();
}

void Renderer::beginPass() {
	m_impl.beginPass();
}

void Renderer::render() {
	m_impl.render();
}

void Renderer::endPass() {
	m_impl.endPass();
}

void Renderer::draw(const Texture& texture, const int32 x_pos, const int32 y_pos) {
	m_impl.draw(texture, x_pos, y_pos);
}

Texture* Renderer::getTexture(const std::string& path, const TextureData& data) {
	return m_impl.createTexture(path, data);
}
}
