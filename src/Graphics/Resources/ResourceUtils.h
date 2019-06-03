#pragma once

#include "Draug.h"
#include "Resource.h"
#include <bgfx/bgfx.h>
#include <bx/file.h>
#include <bx/allocator.h>

namespace Draug {
bool file_exists(const std::string& path);

TextureHandle load_texture(bx::FileReaderI* reader, bx::AllocatorI* allocator, const std::string& path, uint64_t flags, bgfx::TextureInfo* info);
TextureHandle load_texture(bx::AllocatorI* allocator, const std::string& name, void* data, uint32_t size, uint64_t flags, bgfx::TextureInfo* info);

ShaderHandle load_shader(bx::FileReaderI* reader, const std::string& path);
ProgramHandle load_shader_program(bx::FileReaderI* reader, const std::string& name);

UniformHandle create_uniform(const std::string& name, UniformType type, uint16_t num);
void get_uniform_info(UniformHandle handle, UniformInfo& info);
}
