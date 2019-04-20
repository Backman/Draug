
#include <iostream>
#include <Core/Log.h>
#include <Core/Window/Window.h>
#include <Core/Core.h>
#include <Core/Event/Event.h>
#include <Core/Resources/ResourceLoader.h>
#include "Components/ComponentTypes.h"
#include "Systems/SystemTypes.h"

namespace Textures {
enum Type {
	Test,
	Count
};
}

class PlaygroundApp : public Draug::App {
public:
#define BIND_FN(fn) std::bind(&PlaygroundApp::fn, this, std::placeholders::_1)
	Draug::ECS::Scene scene{};
	bool running = false;

	Draug::Resources::ResourceManager<sf::Texture, Textures::Type> textures;

	PlaygroundApp() = default;
	~PlaygroundApp() = default;

	void initialize() override {

		m_window.initialize(Draug::WindowConfig::createWindowed("Playground", 800, 600));
		m_window.registerEventHandler(BIND_FN(onEvent));

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
		scene.addComponent<SpriteComponent>(e, textures.get(Textures::Test, Draug::Resources::fromFile<sf::Texture>(".\\Assets\\test.png")));
		scene.addComponent<DrawableComponent>(e));

		std::cout << "Run" << std::endl;
		running = true;
		while (running) {
			m_window.update();
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
