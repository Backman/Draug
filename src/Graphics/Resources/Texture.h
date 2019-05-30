#pragma once

#include "Draug.h"
#include "Resource.h"
#include "ResourceManager.h"

namespace Draug {

class Texture : public ResourceHandle<TextureHandle> {
public:
	static void load(Texture& texture, bx::FileReaderI* reader, bx::AllocatorI* allocator, const std::string& path);

	Texture() = default;
	~Texture() = default;

	TextureInfo m_info;
	std::string m_path;
};

class TextureManager : public ResourceManager<Texture> {
};
}
