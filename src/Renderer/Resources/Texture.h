#pragma once

#include "Core/Types.h"
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
	uint32 width;
	uint32 height;
	bgfx::TextureFormat::Enum format;
	uint32 storage_size;
	std::string path;
};

class TextureManager : public ResourceManager<Texture> {
};
}
