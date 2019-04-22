#pragma once

#include "Draug.h"
#include "Core/Types.h"

namespace bgfx {
struct TextureHandle;
struct TextureInfo;
}

namespace bx {
struct FileReaderI;
struct AllocatorI;
}

namespace Draug {
namespace bgfxUtils {
static void* load(bx::FileReaderI* reader, bx::AllocatorI* allocator, const std::string& path, uint32* size);
static void unload(bx::AllocatorI* allocator, void* data);
static void releaseBgfxImage(void* ptr, void* data);

bgfx::TextureHandle loadTexture(bx::FileReaderI& reader, bx::AllocatorI& allocator, const std::string& path, uint64 flags, bgfx::TextureInfo* info);
bgfx::TextureHandle loadTexture(bx::AllocatorI& allocator, const std::string& name, void* data, uint32 size, uint64 flags, bgfx::TextureInfo* info);
}
}
