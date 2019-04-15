
#include <iostream>
#include <Core/Log.h>
#include <Core/Core.h>
#include <Core/Core.h>

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

	PlaygroundApp() : world() {
	}
	~PlaygroundApp() {}

	void initialize() override {

		window.initialize(Draug::WindowConfig::createWindowed("Playground", 800, 600));
		world.initialize();
		world.addSystem<MoveSystem>();

		std::cout << "Initialize" << std::endl;
	}

	void run() override {
		Draug::ECS::Entity e = world.getEntityMgr()->create();
		world.getEntityMgr()->addComponent<Position>(e, 12, 12);

		world.update();
		world.update();
		world.update();
		world.update();
		world.update();

		std::cout << "Run" << std::endl;

		while (true) {
			window.display();
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
