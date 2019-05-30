#include "ResourceUtils.h"
#include "Log/Log.h"
#include <bimg/bimg.h>
#include <bimg/decode.h>

namespace Draug {
static bool open_file(bx::FileReaderI* reader, const std::string& path) {
	bx::Error error;
	if (bx::open(reader, path.c_str(), &error) == false) {
		DRAUG_LOG_CORE_ERROR("Failed to open file {0} - Error: {1}", path, error.getMessage().getPtr());
		return false;
	}
	return true;
}

static void* read_file(bx::FileReaderI* reader, bx::AllocatorI* allocator, uint32_t* size, const std::string& path) {
	uint32_t read_size = (uint32_t)bx::getSize(reader);
	void* data = BX_ALLOC(allocator, read_size);
	bx::Error error;
	if (bx::read(reader, data, read_size, &error) == false) {
		if (size != nullptr) {
			*size = 0;
		}
		BX_FREE(allocator, data);
		DRAUG_LOG_CORE_ERROR("Failed to read file {0} - Error: {1}", path, error.getMessage().getPtr());
		return nullptr;
	}
	bx::close(reader);
	if (size != nullptr) {
		*size = read_size;
	}
	return data;
}

static const bgfx::Memory* load_mem(bx::FileReaderI* reader, const std::string& path) {
	if (open_file(reader, path) == false) {
		return nullptr;
	}

	uint32_t size = uint32_t(bx::getSize(reader));
	const bgfx::Memory* mem = bgfx::alloc(size + 1);
	bx::read(reader, mem->data, size);
	bx::close(reader);
	mem->data[mem->size - 1] = '\0';
	return mem;
}

static void* load(bx::FileReaderI* reader, bx::AllocatorI* allocator, const std::string& path, uint32_t* size) {
	if (open_file(reader, path) == false) {
		if (size != nullptr) {
			*size = 0;
		}
		return nullptr;
	}

	uint32_t read_size = (uint32_t)bx::getSize(reader);
	return read_file(reader, allocator, size, path);
}

static void release_bgfx_image(void* ptr, void* data) {
	BX_UNUSED(ptr);
	bimg::ImageContainer* image = (bimg::ImageContainer*)data;
	bimg::imageFree(image);
}

TextureHandle load_texture(bx::FileReaderI* reader, bx::AllocatorI* allocator, const std::string& path, uint64_t flags, bgfx::TextureInfo* info) {
	uint32_t size;
	void* data = load(reader, allocator, path, &size);
	if (data == nullptr) {
		return BGFX_INVALID_HANDLE;
	}
	return load_texture(allocator, path, data, size, flags, info);
}

TextureHandle load_texture(bx::AllocatorI* allocator, const std::string& name, void* data, uint32_t size, uint64_t flags, bgfx::TextureInfo* info) {
	bx::Error error;
	bimg::ImageContainer* image = bimg::imageParse(allocator, data, size);
	BX_FREE(allocator, data);
	if (image == nullptr) {
		DRAUG_LOG_CORE_ERROR("Failed to parse image {0}", name);
		return BGFX_INVALID_HANDLE;
	}

	const bgfx::Memory* mem = bgfx::makeRef(image->m_data, image->m_size, release_bgfx_image, image);

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

bool file_exists(const std::string& path) {
#if defined WIN32
	struct _stat info;
	return _stat(path.c_str(), &info) == 0 && (info.st_mode & _S_IFMT) != 0;
#else 
	struct stat info;
	return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFMT) != 0;
#endif
}

ShaderHandle load_shader(bx::FileReaderI* reader, const std::string& path) {
	if (file_exists(path))
		return bgfx::createShader(load_mem(reader, path));
	else
		return BGFX_INVALID_HANDLE;
}

ProgramHandle load_shader_program(bx::FileReaderI* reader, const std::string& path) {
	const std::string vs_path = path + "_vs";
	const std::string fs_path = path + "_fs";

	bgfx::ShaderHandle vertex_shader = load_shader(reader, vs_path.c_str());
	bgfx::ShaderHandle fragment_shader = load_shader(reader, fs_path.c_str());

	bgfx::ProgramHandle handle = bgfx::createProgram(vertex_shader, fragment_shader, true);

	if (bgfx::isValid(handle)) {
		DRAUG_LOG_CORE_ERROR("Failed to load shader program - {0}", path);
	}
	return handle;
}
UniformHandle create_uniform(const std::string& name, UniformType type, uint16_t num) {
	UniformHandle handle = bgfx::createUniform(name.c_str(), type, num);
	
	if (bgfx::isValid(handle)) {
		DRAUG_LOG_CORE_ERROR("Failed to create uniform - {0}", name);
	}
	return handle;
}
void get_uniform_info(UniformHandle handle, UniformInfo& info) {
	bgfx::getUniformInfo(handle, info);
}
}
