#pragma once

#include "Draug.h"
#include "Core/Types.h"
#include "System.h"
#include "EntityManager.h"

namespace Draug {
class App;
namespace ECS {
class DRAUG_API Scene {
	App* m_app;
	EntityManager* m_entity_mgr;
	SystemManager* m_system_mgr;
public:
	Scene() = default;
	~Scene();

	inline EntityManager* getEntityMgr() const { return m_entity_mgr; }
	inline SystemManager* getSystemMgr() const { return m_system_mgr; }

	void initialize(App* app);
	void shutdown();
	void update();

	Entity createEntity();

	App* getApp() const { return m_app; }

	template<typename T, typename... Args>
	inline Entity createEntity(Args&& ... args) {
		return m_entity_mgr->create<T>(args...);
	}

	void createEntities(uint32 count);

	template<typename T, typename... Args>
	inline void createEntities(uint32 count, Args&& ... args) {
	}

	template<typename T, typename... Args>
	inline void addComponent(const Entity& e, Args&& ... args) {
		m_entity_mgr->addComponent<T>(e, args...);
	}

	template<typename T>
	inline T getComponent(const Entity& e) {
		return m_entity_mgr->getComponent<T>(e);
	}

	template<typename TSystem, typename... Args>
	inline void addSystem(Args&& ... args) {
		m_system_mgr->addSystem<TSystem, Args...>(args...);
	};

	template<typename TSystem>
	inline void getSystem() {
	};
};
}
}
