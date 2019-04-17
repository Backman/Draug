
#include <iostream>
#include <Core/Log.h>
#include <Core/Window/Window.h>
#include <Core/Core.h>
#include <Core/Event/Event.h>
#include "Components/ComponentTypes.h"
#include "Systems/SystemTypes.h"

class PlaygroundApp : public Draug::App {
public:
#define BIND_FN(fn) std::bind(&PlaygroundApp::fn, this, std::placeholders::_1)
	Draug::ECS::Scene scene;
	Draug::Window window{};
	bool running = false;

	PlaygroundApp() = default;
	~PlaygroundApp() = default;

	void initialize() override {
		window.initialize(Draug::WindowConfig::createWindowed("Playground", 800, 600));
		window.registerEventHandler(BIND_FN(onEvent));

		std::cout << "Initialize" << std::endl;
	}

	void onEvent(const Draug::Event& evt) {
		Draug::Event::dispatchEvent<Draug::WindowResizeEvent>(evt, BIND_FN(onResize));
		Draug::Event::dispatchEvent<Draug::WindowCloseEvent>(evt, BIND_FN(onClosed));
	}

	bool onResize(const Draug::WindowResizeEvent& evt) {
		std::cout << "On resize" << std::endl;
		return true;
	}

	bool onClosed(const Draug::WindowCloseEvent& evt) {
		std::cout << "On close" << std::endl;
		running = false;
		return true;
	}

	void run() override {
		scene.initialize(this);
		scene.addSystem<SpriteRenderSystem>();
		auto e = scene.createEntity();
		scene.addComponent<PositionComponent>(e, 0, 0);
		scene.addComponent<SpriteComponent>(e, "Assets\\test.png");

		std::cout << "Run" << std::endl;
		running = true;
		while (running) {
			window.update();
			scene.update();
		}
	}

	void shutdown() override {
		std::cout << "Shutdown" << std::endl;
		scene.shutdown();
	}
};

Draug::App* Draug::createApp() {
	return new PlaygroundApp();
};
