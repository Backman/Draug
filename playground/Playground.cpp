#include <Core/Entry.h>
#include <iostream>
#include <Log/Log.h>
#include <Core/App/App.h>
#include <Core/Window/Window.h>
#include <Core/Event/Event.h>
#include <Graphics/Renderer/Renderer.h>
#include <Input/Input.h>
#include "Systems/RenderDebugStatsSystem.h"
#include <Core/ECS/World.h>
#include <dear-imgui/imgui.h>
#include <bgfx/bgfx.h>
#include "ImGui/ImGui.h"
#include <Graphics/Gfx.h>
#include <Core/ECS/Components/PositionComponent.h>
#include <Core/ECS/Components/RenderComponent.h>
#include <Core/ECS/Systems/RenderSystem.h>
#include "../src/Core/ECS/Systems/MeshRenderSystem.h"

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

struct FollowMouseComponent {
	bool follow;
};

class FollowMouseSystem : public Draug::ECS::ISystem {
public:
	virtual void tick(float dt, World* world) override {
		auto view = world->ecs.view<PositionComponent, FollowMouseComponent>();
		for (auto e : view) {
			auto& follow_mouse = view.get<FollowMouseComponent>(e);
			if (follow_mouse.follow == false) {
				break;
			}
			auto& pos = view.get<PositionComponent>(e);
			Draug::Input::Mouse& mouse = Draug::Input::Input::mouse;
			pos.x = mouse.x_pos();
			pos.y = mouse.y_pos();
		}
	}
};

class TestState : public Draug::State {
public:
	TestState(const Draug::StateContext& context) :
		Draug::State(context, "game_state") {
	}

	inline void on_start() override {
		world()->register_system<FollowMouseSystem>();
		auto e = world()->create_entity<MeshComponent, PositionComponent, FollowMouseComponent>();
		auto& mesh = std::get<1>(e);
		auto& follow_mouse = std::get<3>(e);
		follow_mouse.follow = true;
		mesh.instance = Draug::Mesh::s_triangle;
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

class PlaygroundApp : public Draug::App {
public:
	bool running = false;

	PlaygroundApp() = default;
	~PlaygroundApp() = default;

	void on_init() override {
		Draug::Gfx& gfx = Draug::Gfx::get();
		gfx.init(DRAUG_RESOURCE_PATH);
		gfx.add_resource_path("playground", true);
		m_state_machine.init(new TestState(create_state_context()));
		m_state_machine.start();
	}

	void on_shutdown() override {
	}
};

DRAUG_ENTRY(PlaygroundApp);
