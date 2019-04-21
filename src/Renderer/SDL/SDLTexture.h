#pragma once

#include "Core/Resources/Resource.h"

struct SDL_Texture;

namespace Draug {
class SDLTexture : public Resource {
public:
	RESOURCE_TYPE("sdl_texture2d");

	SDL_Texture* texture;
};
}
