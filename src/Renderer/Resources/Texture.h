#pragma once

#include "Draug.h"
#include "ResourceManager.h"
#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <bx/file.h>
#include <bimg/bimg.h>

namespace Draug {
class Texture {
public:
	Texture() = default;
	~Texture() = default;

	void setData(const bgfx::TextureInfo& info);
	void load(bx::FileReaderI& reader, bx::AllocatorI& allocator, const std::string& path);

	bgfx::TextureHandle handle;
	std::string name;
	uint16_t width;
	uint16_t height;
	bgfx::TextureFormat::Enum format;
	uint32_t storage_size;
	std::string path;
};

class TextureManager : public ResourceManager<Texture> {
};
}
