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

	inline ECS::EntityManager* getEntityMgr() const { return m_entity_mgr; }
	inline ECS::SystemManager* getSystemMgr() const { return m_system_mgr; }

	void initialize(App* app);
	void shutdown();
	void tick(float dt);
	void fixedTick();

	ECS::Entity createEntity();

	template<typename T, typename... Args>
	inline ECS::Entity createEntity(Args&& ... args) {
		return m_entity_mgr->create<T>(args...);
	}

	void createEntities(int count);

	template<typename T, typename... Args>
	inline void createEntities(int count, Args&& ... args) {
	}

	template<typename... TComponents>
	inline ECS::EntityManager::EntityCollection entities() {
		return m_entity_mgr->entities<TComponents...>();
	}

	template<typename T, typename... Args>
	inline World* addComponent(const ECS::Entity& e, Args&& ... args) {
		m_entity_mgr->addComponent<T>(e, args...);
		return this;
	}

	template<typename T>
	inline T& getComponent(const ECS::Entity& e) {
		return m_entity_mgr->getComponent<T>(e);
	}

	template<typename TSystem, typename... Args>
	inline void addSystem(Args&& ... args) {
		m_system_mgr->addSystem<TSystem, Args...>(args...);
	};

	template<typename TSystem>
	inline void getSystem() {
	};
private:
	ECS::EntityManager* m_entity_mgr;
	ECS::SystemManager* m_system_mgr;
	App* m_app;
};
}
