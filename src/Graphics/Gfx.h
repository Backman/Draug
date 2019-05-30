#pragma once

#include "Draug.h"
#include "Core/Util/Singleton.h"
#include "Resources/ResourceManager.h"
#include "Resources/Texture.h"

namespace Draug {
class Gfx : public Singleton<Gfx> {
public:
	void init(const std::string& resource_path);
	std::string& resource_path() { return m_resource_path; }

	void add_resource_path(const std::string& resource_path, bool relative);
	std::string get_full_path(const std::string& name);

	bx::AllocatorI* allocator() { return &m_allocator; }
	bx::FileReaderI* file_reader() { return &m_file_reader; }
	bx::FileWriterI* file_writer() { return &m_file_writer; }

	ResourceManager<Texture>& textures() { return m_textures; }

private:
	std::string m_resource_path;
	std::vector<std::string> m_resource_paths;
	bx::DefaultAllocator m_allocator;
	bx::FileReader m_file_reader;
	bx::FileWriter m_file_writer;

	ResourceManager<Texture> m_textures;
};
}