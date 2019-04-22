
#include <Core/Entry.h>
#include <iostream>
#include <Log/Log.h>
#include <Core/App.h>
#include <Core/Window/Window.h>
#include <Core/Event/Event.h>
#include <Renderer/Resources/Texture.h>
#include <Renderer/Renderer.h>
#include <ECS/Scene.h>
#include <ECS/System.h>
#include <Input/Input.h>
#include "Components/ComponentTypes.h"
#include "Systems/SystemTypes.h"

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
		for (auto e : mgr->entities<PositionComponent, TextureComponent>()) {
			auto& pos = scene->getComponent<PositionComponent>(e);
			auto& texture = scene->getComponent<TextureComponent>(e);
		}
	}
};

class GameState : public Draug::AppState {
public:
	GameState(const Draug::AppStateContext& context) :
		Draug::AppState(context, "game_state") {
	}

	inline void init() override {
		scene.initialize(context.app);
		scene.addSystem<RenderSystem>();
		scene.addSystem<MoveSystem>();

		auto e = scene.createEntity();
		scene.addComponent<PositionComponent>(e, rand() % 1024, rand() % 720);
		scene.addComponent<TextureComponent>(e, nullptr);
		scene.addComponent<PlayerComponent>(e);

		Draug::Texture* test = context.app->getRenderer()->textures.load("D:/workspace/cpp/Draug/.projects/vs2017/Assets", "test.png");
		Draug::uint32 w = test->width;
	}

	inline void shutdown() override {
		scene.shutdown();
	}

	inline void tick() override {
		scene.update();
	}

	Draug::ECS::Scene scene;
};

class PrioState : public Draug::AppState {
};

class PlaygroundApp : public Draug::App {
public:
	bool running = false;

	PlaygroundApp() = default;
	~PlaygroundApp() = default;

	void onInitialize() override {
		addState(new GameState(Draug::AppStateContext{ this }));
	}

	void onShutdown() override {
	}
};

DRAUG_ENTRY(PlaygroundApp);
