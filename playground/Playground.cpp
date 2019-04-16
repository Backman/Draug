
#include <iostream>
#include <Core/Log.h>
#include <Core/Window/Window.h>
#include <Core/Core.h>
#include <Core/Event/Event.h>

struct Position {
	int x, y;
};

class MoveSystem : public Draug::ECS::System<MoveSystem> {
	void tick(Draug::ECS::EntityManager* em, Draug::float32 dt) {
		for (auto e : em->entities<Position>()) {
			Position* p = em->getComponent<Position>(e);
			std::cout << "Position (" << p->x << ", " << p->y << ")" << std::endl;
			p->x++;
			p->y++;
		}
	}
};

class PlaygroundApp : public Draug::App {
public:
	Draug::ECS::World world;
	Draug::Window window;
	bool running;

	PlaygroundApp() : world() {
	}
	~PlaygroundApp() {}

	void initialize() override {

		window.initialize(Draug::WindowConfig::createWindowed("Playground", 800, 600));
		window.registerEventHandler(std::bind(&PlaygroundApp::onEvent, this, std::placeholders::_1));
		world.initialize();
		world.addSystem<MoveSystem>();

		std::cout << "Initialize" << std::endl;
	}

	void onEvent(const Draug::Event& evt) {
		std::cout << "On event" << std::endl;

		Draug::Event::dispatchEvent<Draug::WindowResizeEvent>(evt, std::bind(&PlaygroundApp::onResize, this, std::placeholders::_1));
		Draug::Event::dispatchEvent<Draug::WindowCloseEvent>(evt, std::bind(&PlaygroundApp::onClosed, this, std::placeholders::_1));
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
		running = true;
		Draug::ECS::Entity e = world.getEntityMgr()->create();
		world.getEntityMgr()->addComponent<Position>(e, 12, 12);

		world.update();
		world.update();
		world.update();
		world.update();
		world.update();

		std::cout << "Run" << std::endl;

		while (running) {
			window.update();
		}
	}

	void shutdown() override {
		std::cout << "Shutdown" << std::endl;
		world.shutdown();
	}
};

Draug::App* Draug::createApp() {
	return new PlaygroundApp();
};
