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
			World() = default;
			~World();

			inline EntityManager* getEntityMgr() const { return m_entity_mgr; }
			inline SystemManager* getSystemMgr() const { return m_system_mgr; }

			void initialize();
			void shutdown();
			void update();

			template<typename TSystem, typename... Args>
			inline void addSystem(Args&& ... args) {
				m_system_mgr->addSystem<TSystem, Args...>(args...);
			};
		};
	}
}
