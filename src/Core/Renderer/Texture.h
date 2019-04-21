#pragma once


#include "Core/Renderer/SDL/SDLTexture.h"

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
	TextureFormat::Type format = TextureFormat::Invalid;
	TextureType::Type type = TextureType::Invalid;
	uint32 width;
	uint32 height;
};

class Texture : public SDLTexture {
public:
	TextureData data;
};
}
