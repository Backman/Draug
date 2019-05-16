
#include <Core/Entry.h>
#include <iostream>
#include <Log/Log.h>
#include <Core/App/App.h>
#include <Core/Window/Window.h>
#include <Core/Event/Event.h>
#include <Renderer/Resources/Texture.h>
#include <Renderer/Renderer.h>
#include <Core/World/World.h>
#include <Core/OLD_ECS/System.h>
#include <Input/Input.h>
#include "Components/ComponentTypes.h"
#include "Systems/SystemTypes.h"
#include <Core/ECS/World.h>

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

class MoveSystem : public Draug::OLD_ECS::System {
public:
	void tick(Draug::OLD_ECS::SystemContext& context, float dt) override {
		Draug::World* world = context.world;
		for (auto e : world->entities<PositionComponent, PlayerComponent>()) {
			auto& pos = world->get_component<PositionComponent>(e);
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

class RenderSystem : public Draug::OLD_ECS::System {
public:
	void tick(Draug::OLD_ECS::SystemContext& context, float dt) override {
		for (auto e : context.world->entities<PositionComponent, TextureComponent>()) {
			auto& pos = context.world->get_component<PositionComponent>(e);
			auto& texture = context.world->get_component<TextureComponent>(e);
		}
	}
};

class DebugTextSystem : public Draug::OLD_ECS::System {

public:
	void init(Draug::OLD_ECS::SystemContext& context) override {
		context.app->get_window()->subscribe_event([&](Draug::Event& event)
			{
				Draug::Input::KeyEvent key_event;
				if (Draug::Event::try_cast<Draug::Input::KeyEvent>(event, &key_event) == false) {
					return;
				}
				if (key_event.type == Draug::Input::KeyEvent::Down && key_event.key == Draug::Input::Key::F1) {
					m_show_stats = m_show_stats == false;
				}
			});
	}

	void tick(Draug::OLD_ECS::SystemContext& context, float dt) override {
		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
		bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
		bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
		bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
		const bgfx::Stats* stats = bgfx::getStats();
		bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.",
			stats->width, stats->height, stats->textWidth, stats->textHeight);
		bgfx::setDebug(m_show_stats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
	}
private:
	bool m_show_stats;
	Draug::EventCallbackId m_event_id;
};

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
		world()->add_system<RenderSystem>();
		world()->add_system<MoveSystem>();

		auto e = world()->create_entity();
		world()->add_component<PositionComponent>(e, rand() % 1024, rand() % 720)
			->add_component<TextureComponent>(e, nullptr)
			->add_component<PlayerComponent>(e);

		Draug::Texture* test = app()->get_renderer()->textures.load("D:/workspace/cpp/Draug/.projects/vs2017/Assets", "test.png");
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

class DebugState : public Draug::State {
public:
	DebugState(const Draug::StateContext& context) :
		Draug::State(context, "debug_state") {
	}

	inline void on_start() {
		world()->add_system<DebugTextSystem>();
	}

	inline Draug::StateTransition tick(float dt) override {
		return Draug::StateTransition::to(new TestState(context()));
	}
};

class NewECS : public Draug::State {
	struct TestComp {
		int x;
		int y;
	};
public:
	NewECS(const Draug::StateContext& context) :
		Draug::State(context, "new_ecs_state") {}

	inline void onStart() {
		auto e = world.create_entity();
		world.assign<TestComp>(e);
	}
	Draug::ECS::World world;
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
