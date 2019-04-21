
#include <iostream>
#include <Core/Log.h>
#include <Core/Window/Window.h>
#include <Core/Core.h>
#include <Core/Event/Event.h>
#include <Core/Resources/ResourceLoader.h>
#include <Core/Renderer/Texture.h>
#include <Core/Renderer/Renderer.h>
#include <Core/ECS/System.h>
#include "Components/ComponentTypes.h"
#include "Systems/SystemTypes.h"
#include <SDL/SDL.h>

namespace Textures {
enum Type {
	Test,
	Count
};
}

struct TextureComponent {
	Draug::Texture* texture;
};

class MoveSystem : public Draug::ECS::System {
public:
	virtual void tick(Draug::ECS::Scene* scene, Draug::float32 dt) {
		auto mgr = scene->getEntityMgr();
		for (auto e : mgr->entities<PositionComponent>()) {
			auto& pos = scene->getComponent<PositionComponent>(e);
			pos.x++;
			pos.y++;
			if (pos.x >= 1024) {
				pos.x = 0;
			}
			if (pos.y >= 720) {
				pos.y = 0;
			}
		}
	}
};

class RenderSystem : public Draug::ECS::System {
public:
	virtual void tick(Draug::ECS::Scene* scene, Draug::float32 dt) {
		auto mgr = scene->getEntityMgr();
		Draug::uint32 ticks = SDL_GetTicks();
		Draug::Renderer::beginPass();
		for (auto e : mgr->entities<PositionComponent, TextureComponent>()) {
			auto& pos = scene->getComponent<PositionComponent>(e);
			auto& texture = scene->getComponent<TextureComponent>(e);
			Draug::Renderer::draw(*texture.texture, pos.x, pos.y);
		}
		Draug::Renderer::endPass();
		DRAUG_DEBUG("Render system ticks: {0}", (SDL_GetTicks() - ticks));
	}
};

class PlaygroundApp : public Draug::App {
public:
	Draug::ECS::Scene scene{};
	bool running = false;

	PlaygroundApp() = default;
	~PlaygroundApp() = default;

	void onInitialize() override {
		srand(time(NULL));
		std::cout << "Initialize" << std::endl;

		scene.initialize(this);
		scene.addSystem<RenderSystem>();
		scene.addSystem<MoveSystem>();
		for (size_t i = 0; i < 50; i++) {
			createEntity();
		}
	}

	void createEntity() {
		auto e = scene.createEntity();
		scene.addComponent<PositionComponent>(e, rand() % 1024, rand() % 720);
		Draug::TextureData tex_data;
		tex_data.format = Draug::TextureFormat::RGBA;
		tex_data.type = Draug::TextureType::Tex2D;
		tex_data.width = 32;
		tex_data.height = 32;
		scene.addComponent<TextureComponent>(e, Draug::Renderer::getTexture(tex_data, ".\\Assets\\test.png"));
	}

	void onUpdate() override {
		scene.update();
	}

	void onShutdown() override {
		scene.shutdown();
	}
};

Draug::App* Draug::createApp() {
	return new PlaygroundApp();
};
