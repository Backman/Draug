
#include <Core/Entry.h>
#include <iostream>
#include <Log/Log.h>
#include <Core/App/App.h>
#include <Core/Window/Window.h>
#include <Core/Event/Event.h>
#include <Renderer/Renderer.h>
#include <Core/World/World.h>
#include <Core/OLD_ECS/System.h>
#include <Input/Input.h>
#include "Components/PositionComponent.h"
#include "Systems/RenderDebugStatsSystem.h"
#include <Core/ECS/World.h>

#include "Components/TextureComponent.h"
class PausedState : public Draug::State {
public:
	PausedState(const Draug::StateContext& context) :
		Draug::State(context, "paused_state") {
	}

	inline Draug::StateTransition on_event(Draug::Event& event) override {
		Draug::Input::KeyEvent key_event;
		if (Draug::Event::try_cast<Draug::Input::KeyEvent>(event, &key_event)) {
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
		return Draug::State::on_event(event);
	}
};

class TestState : public Draug::State {
public:
	TestState(const Draug::StateContext& context) :
		Draug::State(context, "game_state") {
	}

	inline void on_start() override {
		auto e = world()->create_entity<TextureComponent>();
		auto& texture = std::get<1>(e);
		texture.texture = app()->get_renderer()->textures.load("./Assets", "test.png");
	}

	inline Draug::StateTransition on_event(Draug::Event& event) override {
		Draug::Input::KeyEvent key_event;
		if (Draug::Event::try_cast<Draug::Input::KeyEvent>(event, &key_event)) {
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
		return Draug::State::on_event(event);
	}
};

struct T {
	int x, y;
};

class DebugState : public Draug::State {
public:
	DebugState(const Draug::StateContext& context) :
		Draug::State(context, "debug_state") {
	}

	inline void on_start() {
		world()->register_system<DebugTextSystem>();
		world()->create_entity<DebugStatsComponent, T>();
	}

	inline Draug::StateTransition tick(float dt) override {
		return Draug::StateTransition::to(new TestState(context()));
	}
};

class PlaygroundApp : public Draug::App {
public:
	bool running = false;

	PlaygroundApp() = default;
	~PlaygroundApp() = default;

	void on_init() override {
		m_state_machine.init(new DebugState(Draug::StateContext{ &m_world, this }));
		m_state_machine.start();
	}

	void on_shutdown() override {
	}
};

DRAUG_ENTRY(PlaygroundApp);
