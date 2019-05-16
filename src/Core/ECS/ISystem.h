#pragma once

namespace Draug {
namespace ECS {
class ISystem {
public:
	virtual void init() {}
	virtual void tick(float dt) {}
	virtual void fixed_tick(float fixed_dt) {}
	virtual void shutdown() {}
};
}
}
