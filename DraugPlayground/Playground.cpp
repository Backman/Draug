
#include <iostream>
#include <Draug.h>
#include <Core/ECS/World.h>
#include <Core/Core.h>

struct position {
	int x, y;
};

class MoveSystem : public Draug::ECS::System<MoveSystem> {
	void tick(Draug::ECS::EntityManager* em, Draug::float32 dt) {
		for (auto e : em->entities<position>()) {
			auto p = e.getComponent<position>();
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
	~PlaygroundApp() = default;

	void initialize() override {
		m_world.initialize();
		m_world.addSystem<MoveSystem>();

		std::cout << "Initialize" << std::endl;
	}

	void run() override {
		Draug::ECS::Entity e = m_world.createEntity();
		e.addComponent<position>(12, 12);

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
