#pragma once

#include "Draug.h"
#include "Core/ECS/System.h"
#include "Core/ECS/EntityManager.h"

namespace Draug {
class App;

class DRAUG_API World {
public:
	World() = default;
	~World();

	inline ECS::EntityManager* get_entity_mgr() const { return m_entity_mgr; }
	inline ECS::SystemManager* get_system_mgr() const { return m_system_mgr; }

	void init(App* app);
	void shutdown();
	void tick(float dt);
	void fixed_tick(float fixed_dt);

	ECS::Entity create_entity();

	template<typename T, typename... Args>
	inline ECS::Entity create_entity(Args&& ... args) {
		return m_entity_mgr->create<T>(args...);
	}

	void create_entities(int count);

	template<typename T, typename... Args>
	inline void create_entities(int count, Args&& ... args) {
	}

	template<typename... TComponents>
	inline ECS::EntityManager::EntityCollection entities() {
		return m_entity_mgr->entities<TComponents...>();
	}

	template<typename T, typename... Args>
	inline World* add_component(const ECS::Entity& e, Args&& ... args) {
		m_entity_mgr->add_component<T>(e, args...);
		return this;
	}

	template<typename T>
	inline T& get_component(const ECS::Entity& e) {
		return m_entity_mgr->get_component<T>(e);
	}

	template<typename TSystem, typename... Args>
	inline void add_system(Args&& ... args) {
		m_system_mgr->add_system<TSystem, Args...>(args...);
	};
private:
	ECS::EntityManager* m_entity_mgr;
	ECS::SystemManager* m_system_mgr;
	App* m_app;
};
}
