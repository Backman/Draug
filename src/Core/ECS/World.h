#pragma once

#include "ISystem.h"
#include "ECS.h"
#include "Core/App/App.h"

namespace Draug {
namespace ECS {

class World {
public:
	void init(App* app) {
		this->app = app;
	}

	void shutdown() {
		while (m_systems.empty() == false) {
			ISystem* system = m_systems.back();
			system->shutdown(this);
			delete system;
			m_systems.pop_back();
		}
	}

	template<typename... Component>
	decltype(auto) create_entity() {
		return ecs.create<Component...>();
	}

	void destroy_entity(entity e) {
		ecs.destroy(e);
	}

	template<typename TComponent, typename... Args>
	TComponent& assign(const entity e, Args&&... args) {
		return ecs.assign<TComponent>(e, args...);
	}

	template<typename TSystem>
	TSystem* register_system(TSystem* system) {
		m_systems.emplace_back(system);
		system->init(this);
		return system;
	}

	template<typename TSystem, typename... Args>
	TSystem* register_system(Args&& ... args) {
		return register_system(new TSystem(std::forward<Args>(args)...));
	}

	void tick(float dt) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->tick(dt, this);
		}
	}

	void fixed_tick(float fixed_dt) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->fixed_tick(fixed_dt, this);
		}
	}

	registry ecs;
	dispatcher dispatcher;
	App* app;

private:
	std::vector<ISystem*> m_systems;
};
}
}
