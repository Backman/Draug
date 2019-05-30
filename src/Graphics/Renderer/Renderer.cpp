#include "Renderer.h"
#include "Core/Window/Window.h"

namespace Draug {
void Renderer::init(Window* window) {
	RenderAPI::init(window);

	textures.set_loader([&](Texture & texture, const std::string & path)
		{
			texture.load(m_file_reader, m_allocator, path);
		});
}
}