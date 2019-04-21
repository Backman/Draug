
#include <iostream>
#include <Core/Log.h>
#include <Core/Window/Window.h>
#include <Core/Core.h>
#include <Core/Event/Event.h>
#include <Core/Resources/ResourceLoader.h>
#include <Core/Renderer/Texture.h>
#include <Core/Renderer/Renderer.h>
#include <Core/ECS/System.h>
#include <Input/Input.h>
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

struct PlayerComponent {
};

class MoveSystem : public Draug::ECS::System {
public:
	virtual void tick(Draug::ECS::Scene* scene, Draug::float32 dt) {
		auto mgr = scene->getEntityMgr();
		for (auto e : mgr->entities<PositionComponent, PlayerComponent>()) {
			auto& pos = scene->getComponent<PositionComponent>(e);
			if (Draug::Input::Input::keyboard.isKeyPressed(SDL_SCANCODE_LEFT)) {
				pos.x--;
			}
			if (Draug::Input::Input::keyboard.isKeyPressed(SDL_SCANCODE_RIGHT)) {
				pos.x++;
			}
			if (Draug::Input::Input::keyboard.isKeyPressed(SDL_SCANCODE_UP)) {
				pos.y--;
			}
			if (Draug::Input::Input::keyboard.isKeyPressed(SDL_SCANCODE_DOWN)) {
				pos.y++;
			}
			if (pos.x > 1024) {
				pos.x = 1024;
			}
			else if (pos.x < 0) {
				pos.x = 0;
			}
			if (pos.y > 720) {
				pos.y = 720;
			}
			else if (pos.y < 0) {
				pos.y = 0;
			}
		}
	}
};

class RenderSystem : public Draug::ECS::System {
public:
	virtual void tick(Draug::ECS::Scene* scene, Draug::float32 dt) {
		auto mgr = scene->getEntityMgr();
		Draug::Renderer::beginPass();
		for (auto e : mgr->entities<PositionComponent, TextureComponent>()) {
			auto& pos = scene->getComponent<PositionComponent>(e);
			auto& texture = scene->getComponent<TextureComponent>(e);
			Draug::Renderer::draw(*texture.texture, pos.x, pos.y);
		}
		Draug::Renderer::endPass();
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
		createPlayer();
	}

	void createPlayer() {
		auto e = scene.createEntity();
		scene.addComponent<PositionComponent>(e, rand() % 1024, rand() % 720);
		scene.addComponent<TextureComponent>(e, Draug::Renderer::getTexture(".\\Assets\\test.png"));
		scene.addComponent<PlayerComponent>(e);
	}

	void onUpdate() override {
		if (Draug::Input::Input::keyboard.isKeyPressed(SDL_SCANCODE_SPACE)) {
			DRAUG_DEBUG("Space is down");
		}
		if (Draug::Input::Input::keyboard.isKeyDown(SDL_SCANCODE_SPACE)) {
			DRAUG_DEBUG("Space is pressed");
		}
		if (Draug::Input::Input::keyboard.isKeyUp(SDL_SCANCODE_SPACE)) {
			DRAUG_DEBUG("Space is released");
		}
		scene.update();
	}

	void onShutdown() override {
		scene.shutdown();
	}
};

Draug::App* Draug::createApp() {
	return new PlaygroundApp();
};
