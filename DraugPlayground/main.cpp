
#include <iostream>
#include <Core/ECS/World.h>

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

int main() {
	Draug::ECS::World world;
	world.initialize();
	Draug::ECS::Entity e = world.createEntity();
	e.addComponent<position>(12, 12);

	world.addSystem<MoveSystem>();

	world.update();
	world.update();
	world.update();
	world.update();
	world.update();

	world.shutdown();
	return 0;
}