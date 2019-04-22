#pragma once

#include "RenderAPI.h"
#include "Resources/Texture.h"

namespace Draug {
class Renderer : public RenderAPI {
public:
	virtual void init(Window* window) override;

	TextureManager textures;
};
}
