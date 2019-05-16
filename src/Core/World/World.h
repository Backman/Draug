#pragma once

#include "Draug.h"
#include "Core/OLD_ECS/System.h"
#include "Core/OLD_ECS/EntityManager.h"

namespace Draug {
class App;

class DRAUG_API World {
public:
	World() = default;
	~World();

	inline OLD_ECS::EntityManager* get_entity_mgr() const { return m_entity_mgr; }
	inline OLD_ECS::SystemManager* get_system_mgr() const { return m_system_mgr; }

	void init(App* app);
	void shutdown();
	void tick(float dt);
	void fixed_tick(float fixed_dt);

	OLD_ECS::Entity create_entity();

	template<typename T, typename... Args>
	inline OLD_ECS::Entity create_entity(Args&& ... args) {
		return m_entity_mgr->create<T>(args...);
	}

	void create_entities(int count);

	template<typename T, typename... Args>
	inline void create_entities(int count, Args&& ... args) {
	}

	template<typename... TComponents>
	inline OLD_ECS::EntityManager::EntityCollection entities() {
		return m_entity_mgr->entities<TComponents...>();
	}

	template<typename T, typename... Args>
	inline World* add_component(const OLD_ECS::Entity& e, Args&& ... args) {
		m_entity_mgr->add_component<T>(e, args...);
		return this;
	}

	template<typename T>
	inline T& get_component(const OLD_ECS::Entity& e) {
		return m_entity_mgr->get_component<T>(e);
	}

	template<typename TSystem, typename... Args>
	inline void add_system(Args&& ... args) {
		m_system_mgr->add_system<TSystem, Args...>(args...);
	};
private:
	OLD_ECS::EntityManager* m_entity_mgr;
	OLD_ECS::SystemManager* m_system_mgr;
	App* m_app;
};
}
