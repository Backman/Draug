
#include <Core/Entry.h>
#include <iostream>
#include <Log/Log.h>
#include <Core/App/App.h>
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
	virtual void tick(Draug::ECS::Scene* scene, float dt) {
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
	virtual void tick(Draug::ECS::Scene* scene, float dt) {
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
		m_scene.initialize(context.app);
		m_scene.addSystem<RenderSystem>();
		m_scene.addSystem<MoveSystem>();

		auto e = m_scene.createEntity();
		m_scene.addComponent<PositionComponent>(e, rand() % 1024, rand() % 720);
		m_scene.addComponent<TextureComponent>(e, nullptr);
		m_scene.addComponent<PlayerComponent>(e);

		Draug::Texture* test = context.app->getRenderer()->textures.load("D:/workspace/cpp/Draug/.projects/vs2017/Assets", "test.png");
	}

	inline void shutdown() override {
		m_scene.shutdown();
	}

	inline void tick() override {
		m_scene.update();
	}

	inline bool onEvent(const Draug::Event& event) override {
		return Draug::Event::dispatch<Draug::Input::KeyEvent>(event, BIND_FN(GameState, onKeyEvent));
	}

private:
	bool onKeyEvent(const Draug::Input::KeyEvent& event) {
		switch (event.type) {
			case Draug::Input::KeyEvent::Down:
			{
				if (event.key == SDL_Scancode::SDL_SCANCODE_ESCAPE) {
					context.app->stop();
				}
			}
			break;
			default:
				break;
		}
		return true;
	}
	Draug::ECS::Scene m_scene;
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
