#pragma once

#include "Components/ComponentTypes.h"
#include <Core/ECS/System.h>
#include <Core/Resources/ResourceManager.h>
#include <SFML/Graphics/Image.hpp>

class SpriteRenderSystem : public Draug::ECS::System {
public:
	void init(Draug::ECS::Scene* scene) override {
	}

	int count = 0;
	void tick(Draug::ECS::Scene* scene, Draug::float32 dt) override {
		auto entities = scene->getEntityMgr()->entities<PositionComponent, SpriteComponent>();
		for (auto e : entities) {
			SpriteComponent& sprite = scene->getComponent<SpriteComponent>(e);
			PositionComponent& pos = scene->getComponent<PositionComponent>(e);

			sf::Image& image = scene->getApp()->images.get(sprite.filename);

			int i = 0;
			i++;
		}
	}

	void shutdown(Draug::ECS::Scene* scene) override {
	}
};
