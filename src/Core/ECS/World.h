#pragma once

#include "entt/entity/registry.hpp"
#include "ISystem.h"

namespace Draug {
namespace ECS {

class World {
public:
	typedef entt::registry::entity_type entity;

	entity create_entity() {
		return ecs.create();
	}

	template<typename TComponent, typename... Args>
	TComponent& assign(const entity e, Args&&... args) {
		return ecs.assign<TComponent>(e, args...);
	}

	template<typename TSystem>
	TSystem* register_system(TSystem* system) {
		m_systems.emplace_back(system);
		system->init();
		return system;
	}

	template<typename TSystem, typename... Args>
	TSystem* register_system(Args&& ... args) {
		return register_system(new TSystem(std::forward<Args>(args)...));
	}

	void tick(float dt) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->tick(dt);
		}
	}

	void fixed_tick(float fixed_dt) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->fixed_tick(fixed_dt);
		}
	}

	entt::registry ecs;

private:
	
	std::vector<ISystem*> m_systems;
};
}
}
