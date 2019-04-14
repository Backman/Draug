#pragma once

#include "Draug.h"
#include "System.h"
#include "EntityManager.h"

namespace Draug {
	namespace ECS {
		class DRAUG_API World {
			EntityManager* m_entity_mgr;
			SystemManager* m_system_mgr;

		public:
			inline void initialize() {
				m_entity_mgr = new EntityManager();
				m_system_mgr = new SystemManager(m_entity_mgr);
			}

			inline void shutdown() {
				delete m_entity_mgr;
				delete m_system_mgr;
			}

			EntityManager* getEntityMgr() const {
				return m_entity_mgr;
			}

			SystemManager* getSystemMgr() const {
				return m_system_mgr;
			}

			void update() {
				m_system_mgr->tick(0);
			}

			Entity createEntity() {
				Entity e = m_entity_mgr->create();
				return e;
			}

			template<typename TSystem, typename... Args>
			inline void addSystem(Args&& ... args) {
				m_system_mgr->addSystem<TSystem, Args...>(args...);
			};
		};
	}
}
