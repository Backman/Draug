#pragma once

#include "World.h"

namespace Draug {
namespace ECS {
class ISystem {
public:
	virtual void init(World* world) {}
	virtual void tick(float dt, World* world) {}
	virtual void fixed_tick(float fixed_dt, World* world) {}
	virtual void shutdown(World* world) {}
};
}
}
