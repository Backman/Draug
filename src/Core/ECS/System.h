#pragma once

#include "Draug.h"

namespace Draug {
class World;
class App;

namespace ECS {
struct SystemContext {
	Draug::World* world;
	Draug::App* app;
};

class DRAUG_API System {
public:
	virtual void init(SystemContext& context) {}
	virtual void tick(SystemContext& context, float dt) {}
	virtual void fixed_tick(SystemContext& context, float fixed_dt) {}
	virtual void shutdown(SystemContext& context) {}
};

class SystemManager {
public:
	SystemManager() = default;
	~SystemManager() {
		while (m_systems.empty() == false) {
			delete m_systems.back();
			m_systems.pop_back();
		}
	}

	void init(const SystemContext& context) {
		m_context = context;
	}

	template<typename TSystem>
	inline void add_system(TSystem* s) {
		m_systems.emplace_back(s);
		s->init(m_context);
	}

	template<typename TSystem, typename... Args>
	inline void add_system(Args&& ... args) {
		TSystem* s = new TSystem(std::forward(args)...);
		return add_system(s);
	}

	void tick(float dt) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->tick(m_context, dt);
		}
	}

	void fixed_tick(float fixed_dt) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->fixed_tick(m_context, fixed_dt);
		}
	}
private:
	std::vector<System*> m_systems;
	SystemContext m_context;
};
}
}
