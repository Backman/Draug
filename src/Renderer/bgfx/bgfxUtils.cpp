#include "bgfxUtils.h"
#include "Log/Log.h"
#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <bx/file.h>
#include <bimg/bimg.h>
#include <bimg/decode.h>

namespace Draug {
namespace bgfxUtils {
void* load(bx::FileReaderI* reader, bx::AllocatorI* allocator, const std::string& path, uint32* size) {
	bx::Error error;
	if (bx::open(reader, path.c_str(), &error) == false) {
		if (size != nullptr) {
			*size = 0;
		}
		DRAUG_LOG_CORE_ERROR("Failed to open file {0} - Error: {1}", path, error.getMessage().getPtr());
		return nullptr;
	}

	uint32 read_size = (uint32)bx::getSize(reader);
	void* data = BX_ALLOC(allocator, read_size);
	error.reset();
	bx::read(reader, data, read_size, &error);
	if (error.isOk() == false) {
		if (size != nullptr) {
			*size = 0;
		}
		DRAUG_LOG_CORE_ERROR("Failed to read file {0} - Error: {1}", path, error.getMessage().getPtr());
		return nullptr;
	}
	bx::close(reader);
	if (size != nullptr) {
		*size = read_size;
	}
	return data;
}

void unload(bx::AllocatorI* allocator, void* data) {
	BX_FREE(allocator, data);
}

void releaseBgfxImage(void* ptr, void* data) {
	BX_UNUSED(ptr);
	bimg::ImageContainer* image = (bimg::ImageContainer*)data;
	bimg::imageFree(image);
}

bgfx::TextureHandle loadTexture(bx::FileReaderI& reader, bx::AllocatorI& allocator, const std::string& path, uint64 flags, bgfx::TextureInfo* info) {
	uint32 size;
	void* data = bgfxUtils::load(&reader, &allocator, path, &size);
	if (data == nullptr) {
		return BGFX_INVALID_HANDLE;
	}
	return loadTexture(allocator, path, data, size, flags, info);
}

bgfx::TextureHandle loadTexture(bx::AllocatorI& allocator, const std::string& name, void* data, uint32 size, uint64 flags, bgfx::TextureInfo* info) {
	bx::Error error;
	bimg::ImageContainer* image = bimg::imageParse(&allocator, data, size);
	bgfxUtils::unload(&allocator, data);
	if (image == nullptr) {
		DRAUG_LOG_CORE_ERROR("Failed to parse image {0}", name);
		return BGFX_INVALID_HANDLE;
	}

	const bgfx::Memory* mem = bgfx::makeRef(image->m_data, image->m_size, bgfxUtils::releaseBgfxImage, image);

	bgfx::TextureHandle handle;
	if (image->m_cubeMap) {
		handle = bgfx::createTextureCube(uint16_t(image->m_width), 1 < image->m_numMips
			, image->m_numLayers, bgfx::TextureFormat::Enum(image->m_format), flags, mem);
	}
	else if (1 < image->m_depth) {
		handle = bgfx::createTexture3D(uint16_t(image->m_width), uint16_t(image->m_height), uint16_t(image->m_depth),
			1 < image->m_numMips, bgfx::TextureFormat::Enum(image->m_format), flags, mem);
	}
	else if (bgfx::isTextureValid(0, false, image->m_numLayers, bgfx::TextureFormat::Enum(image->m_format), flags)) {
		handle = bgfx::createTexture2D(image->m_width, image->m_height, image->m_numMips > 1,
			image->m_numLayers, bgfx::TextureFormat::Enum(image->m_format), flags, mem);
	}
	else {
		DRAUG_LOG_CORE_ERROR("Invalid texture {0}", name);
		return BGFX_INVALID_HANDLE;
	}
	if (info != nullptr) {
		bgfx::calcTextureSize(*info, uint16_t(image->m_width), uint16_t(image->m_height), uint16_t(image->m_depth),
			image->m_cubeMap, 1 < image->m_numMips, image->m_numLayers, bgfx::TextureFormat::Enum(image->m_format));
	}

	if (bgfx::isValid(handle)) {
		DRAUG_LOG_CORE_DEBUG("Loaded texture {0} - Handle: {1}", name, handle.idx);
		bgfx::setName(handle, name.c_str());
	}
	else {
		DRAUG_LOG_CORE_DEBUG("Failed to load texture {0}", name);
	}
	return handle;
}
}
}
