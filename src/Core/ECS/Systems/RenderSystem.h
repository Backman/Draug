#pragma once

#include "Core/ECS/ISystem.h"
#include "Core/ECS/Components/PositionComponent.h"
#include "Core/ECS/Components/RenderComponent.h"

namespace Draug {
namespace ECS {
class RenderSystem : public ISystem {
	virtual void tick(float dt, World* world) {
		auto view = world->ecs.view<PositionComponent, RenderComponent>();
		Draug::Renderer* rendere = world->app->get_renderer();
		for (auto e : view) {
			RenderComponent& render = view.get<RenderComponent>(e);
			PositionComponent& position = view.get<PositionComponent>(e);
		}
	}
};
}
}
