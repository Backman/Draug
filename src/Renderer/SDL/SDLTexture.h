#pragma once

#include "Core/Resources/Resource.h"
#include <SDL/SDL.h>

namespace Draug {
class SDLTexture : public Resource {
public:
	SDL_Texture* texture;

	RESOURCE_TYPE("sdl_texture2d")
};
}
