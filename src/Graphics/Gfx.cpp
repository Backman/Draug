#include "Gfx.h"
#include "Resources/ResourceUtils.h"

namespace Draug {
void Gfx::init(const std::string& resource_path) {
	m_resource_path = resource_path;
	add_resource_path(resource_path, false);
	m_textures.init("/textures", [&](Texture & texture, const std::string & path, const EmptyConfig & config)
		{
			Texture::load(texture, file_reader(), allocator(), path);
		});
}

void Gfx::add_resource_path(const std::string& resource_path, bool relative) {
	m_resource_paths.emplace_back(relative ? m_resource_path + "/" + resource_path : resource_path);
}

std::string Gfx::get_full_path(const std::string& file) {
	for (const std::string& path : m_resource_paths) {
		std::string file_path = path + "/" + file;
		if (file_exists(file_path)) {
			return file_path;
		}
	}
	return {};
}
}