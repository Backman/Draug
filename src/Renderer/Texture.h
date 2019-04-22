#pragma once

namespace Draug {

struct TextureFormat {
	enum Type {
		RGB = 0,
		RGBA,
		Count,
		Invalid = 0xFFFFFFFF
	};
};

struct TextureType {
	enum Type {
		Tex2D = 0,
		Count,
		Invalid = 0xFFFFFFFF
	};
};

struct TextureData {
	TextureFormat::Type format = TextureFormat::RGBA;
	TextureType::Type type = TextureType::Tex2D;
	uint32 width = 0;
	uint32 height = 0;
};
}

//#if DRAUG_SDL_RENDERER
#include "SDL/SDLTexture.h"
namespace Draug {
class Texture : public SDLTexture {
//#elif DRAUG_BGFX_RENDERER
//#include "bgfx/bgfxTexture.h"
//namespace Draug {
//class Texture : public bgfxTexture {
//#endif
public:
	TextureData data;
};
}
