#include "Texture.h"
#include "Renderer/bgfx/bgfxUtils.h"

namespace Draug {
void Texture::setData(const bgfx::TextureInfo& info) {
	width = info.width;
	height = info.height;
	format = info.format;
	storage_size = info.storageSize;
}

void Texture::load(bx::FileReaderI& reader, bx::AllocatorI& allocator, const std::string& path) {
	bgfx::TextureInfo info;
	this->path = path;
	handle = bgfxUtils::loadTexture(reader, allocator, path, BGFX_TEXTURE_NONE, &info);
	setData(info);
}
}