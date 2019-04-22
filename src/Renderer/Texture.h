#pragma once


#include "SDL/SDLTexture.h"

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

class Texture : public SDLTexture {
public:
	TextureData data;
};
}
