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

	inline OLD_ECS::EntityManager* getEntityMgr() const { return m_entity_mgr; }
	inline OLD_ECS::SystemManager* getSystemMgr() const { return m_system_mgr; }

	void initialize(App* app);
	void shutdown();
	void tick(float dt);
	void fixedTick();

	OLD_ECS::Entity createEntity();

	template<typename T, typename... Args>
	inline OLD_ECS::Entity createEntity(Args&& ... args) {
		return m_entity_mgr->create<T>(args...);
	}

	void createEntities(int count);

	template<typename T, typename... Args>
	inline void createEntities(int count, Args&& ... args) {
	}

	template<typename... TComponents>
	inline OLD_ECS::EntityManager::EntityCollection entities() {
		return m_entity_mgr->entities<TComponents...>();
	}

	template<typename T, typename... Args>
	inline World* addComponent(const OLD_ECS::Entity& e, Args&& ... args) {
		m_entity_mgr->addComponent<T>(e, args...);
		return this;
	}

	template<typename T>
	inline T& getComponent(const OLD_ECS::Entity& e) {
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
	OLD_ECS::EntityManager* m_entity_mgr;
	OLD_ECS::SystemManager* m_system_mgr;
	App* m_app;
};
}
