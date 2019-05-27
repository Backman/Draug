#pragma once

#include <Core/ECS/ISystem.h>
#include "../Components/PositionComponent.h"
#include "../Components/TextureComponent.h"

using namespace Draug::ECS;

class RenderSystem : public ISystem {
	virtual void tick(float dt, World* world) {
		auto view = world->ecs.view<PositionComponent, TextureComponent>();
		Draug::Renderer* rendere = world->app->get_renderer();
		for (auto e : view) {
			PositionComponent& position = view.get<PositionComponent>(e);
			TextureComponent& texture = view.get<TextureComponent>(e);

		}
	}
};
