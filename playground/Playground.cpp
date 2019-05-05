
#include <Core/Entry.h>
#include <iostream>
#include <Log/Log.h>
#include <Core/App/App.h>
#include <Core/Window/Window.h>
#include <Core/Event/Event.h>
#include <Renderer/Resources/Texture.h>
#include <Renderer/Renderer.h>
#include <Core/World/World.h>
#include <Core/ECS/System.h>
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
	virtual void tick(Draug::ECS::SystemContext& context, float dt) {
		Draug::World* world = context.world;
		for (auto e : world->entities<PositionComponent, PlayerComponent>()) {
			auto& pos = world->getComponent<PositionComponent>(e);
			if (Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::Left)) {
				pos.x--;
			}
			if (Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::Right)) {
				pos.x++;
			}
			if (Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::Up)) {
				pos.y--;
			}
			if (Draug::Input::Input::keyboard.isKeyPressed(Draug::Input::Key::Down)) {
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
	virtual void tick(const Draug::ECS::SystemContext& context, float dt) {
		for (auto e : context.world->entities<PositionComponent, TextureComponent>()) {
			auto& pos = context.world->getComponent<PositionComponent>(e);
			auto& texture = context.world->getComponent<TextureComponent>(e);
		}
	}
};

class PausedState : public Draug::State {
public:
	PausedState(const Draug::StateContext& context) :
		Draug::State(context, "paused_state") {
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
					if (key_event.key == Draug::Input::Key::Escape) {
						return Draug::StateTransition::pop();
					}
				}
				break;
				default:
					break;
			}
		}
		return Draug::State::onEvent(event);
	}
};

class TestState : public Draug::State {
public:
	TestState(const Draug::StateContext& context) :
		Draug::State(context, "game_state") {
	}

	inline void onStart() override {
		world()->addSystem<RenderSystem>();
		world()->addSystem<MoveSystem>();

		auto e = world()->createEntity();
		world()->addComponent<PositionComponent>(e, rand() % 1024, rand() % 720)
			->addComponent<TextureComponent>(e, nullptr)
			->addComponent<PlayerComponent>(e);

		Draug::Texture* test = app()->getRenderer()->textures.load("D:/workspace/cpp/Draug/.projects/vs2017/Assets", "test.png");
	}

	inline void onStop() override {
	}

	inline Draug::StateTransition tick(float dt) override {
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
					if (key_event.key == Draug::Input::Key::Escape) {
						return Draug::StateTransition::quit();
					}
					else if (key_event.key == Draug::Input::Key::P) {
						return Draug::StateTransition::push(new PausedState(context()));
					}
				}
				break;
				default:
					break;
			}
		}
		return Draug::State::onEvent(event);
	}
};

class PlaygroundApp : public Draug::App {
public:
	bool running = false;

	PlaygroundApp() = default;
	~PlaygroundApp() = default;

	void onInitialize() override {
		m_state_machine.init(new TestState(Draug::StateContext{ &m_world, this }));
		m_state_machine.start();
	}

	void onShutdown() override {
	}
};

DRAUG_ENTRY(PlaygroundApp);
