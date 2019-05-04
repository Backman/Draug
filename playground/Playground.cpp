
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

class PausedState : public Draug::State {
public:
	PausedState() :
		Draug::State("paused_state") {
	}

	inline void onStart() override {
		DRAUG_LOG_DEBUG("Paused on start");
	}

	inline void onStop() override {
		DRAUG_LOG_DEBUG("Paused on stop");
	}

	inline Draug::StateTransition onEvent(Draug::Event& event) override {
		Draug::Input::KeyEvent key_event;
		if (Draug::Event::tryCast<Draug::Input::KeyEvent>(event, &key_event)) {
			switch (key_event.type) {
				case Draug::Input::KeyEvent::Down:
				{
					if (key_event.key == SDL_Scancode::SDL_SCANCODE_ESCAPE) {
						return Draug::StateTransition::pop();
					}
				}
				break;
				default:
					break;
			}
		}
	}
};

class TestState : public Draug::State {
public:
	TestState(const Draug::StateContext& context) :
		Draug::State("game_state"), context(context) {
	}

	inline void onStart() override {
		m_scene.initialize(context.app);
		m_scene.addSystem<RenderSystem>();
		m_scene.addSystem<MoveSystem>();

		auto e = m_scene.createEntity();
		m_scene.addComponent<PositionComponent>(e, rand() % 1024, rand() % 720);
		m_scene.addComponent<TextureComponent>(e, nullptr);
		m_scene.addComponent<PlayerComponent>(e);

		Draug::Texture* test = context.app->getRenderer()->textures.load("D:/workspace/cpp/Draug/.projects/vs2017/Assets", "test.png");
	}

	inline void onStop() override {
		m_scene.shutdown();
	}

	inline Draug::StateTransition tick(float dt) override {
		m_scene.update();

		return Draug::State::tick(dt);
	}

	inline void onPause() override {
		DRAUG_LOG_DEBUG("onPause");
	}

	inline void onResume() override {
		DRAUG_LOG_DEBUG("onResume");
	}

	inline Draug::StateTransition onEvent(Draug::Event& event) override {
		Draug::Input::KeyEvent key_event;
		if (Draug::Event::tryCast<Draug::Input::KeyEvent>(event, &key_event)) {
			switch (key_event.type) {
				case Draug::Input::KeyEvent::Down:
				{
					if (key_event.key == SDL_Scancode::SDL_SCANCODE_ESCAPE) {
						return Draug::StateTransition::quit();
					}
					else if (key_event.key == SDL_SCANCODE_P) {
						return Draug::StateTransition::push(new PausedState());
					}
				}
				break;
				default:
					break;
			}
		}
	}

private:
	Draug::StateContext context;
	Draug::ECS::Scene m_scene;
};

class PlaygroundApp : public Draug::App {
public:
	bool running = false;

	PlaygroundApp() = default;
	~PlaygroundApp() = default;

	void onInitialize() override {
		m_state_machine.init(new TestState(Draug::StateContext{ this }));
		m_state_machine.start();
	}

	void onShutdown() override {
	}
};

DRAUG_ENTRY(PlaygroundApp);
