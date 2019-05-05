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
	virtual void fixedTick(SystemContext& context) {}
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

	void initialize() {
	}

	template<typename TSystem>
	inline void addSystem(TSystem* s) {
		m_systems.emplace_back(s);
	}

	template<typename TSystem, typename... Args>
	inline void addSystem(Args&& ... args) {
		TSystem* s = new TSystem(std::forward(args)...);
		return addSystem(s);
	}

	void tick(SystemContext& context, float dt) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->tick(context, dt);
		}
	}

	void fixedTick(SystemContext& context) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->fixedTick(context);
		}
	}
private:
	std::vector<System*> m_systems;
};
}
}