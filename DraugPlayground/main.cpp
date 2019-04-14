
#include <iostream>
#include <Core/ECS/World.h>

struct position {
	int x, y;
};

class MoveSystem : public Creo::ECS::System<MoveSystem> {
	void tick(Creo::ECS::EntityManager* em, Creo::float32 dt) {
		for (auto e : em->entities<position>()) {
			auto p = e.getComponent<position>();
			std::cout << "Position (" << p->x << ", " << p->y << ")" << std::endl;
			p->x++;
			p->y++;
		}
	}
};

int main() {
	Creo::ECS::World world;
	world.initialize();
	Creo::ECS::Entity e = world.createEntity();
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