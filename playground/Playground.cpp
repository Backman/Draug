
#include <iostream>
#include <Core/Log.h>
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
	Draug::ECS::World m_world;
public:
	PlaygroundApp() : m_world() {
	}
	~PlaygroundApp() {}

	void initialize() override {

		m_world.initialize();
		m_world.addSystem<MoveSystem>();

		std::cout << "Initialize" << std::endl;
	}

	void run() override {
		Draug::ECS::Entity e = m_world.createEntity();
		m_world.getEntityMgr()->addComponent<Position>(e, 12, 12);

		m_world.update();
		m_world.update();
		m_world.update();
		m_world.update();
		m_world.update();

		std::cout << "Run" << std::endl;
	}

	void shutdown() override {
		std::cout << "Shutdown" << std::endl;
		m_world.shutdown();
	}
};

Draug::App* Draug::createApp() {
	return new PlaygroundApp();
};
