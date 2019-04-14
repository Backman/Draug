#pragma once

#include <vector>
#include "types.h"
#include "EntityManager.h"

namespace Draug {
	namespace ECS {
		class DRAUG_API BaseSystem {
		public:
			virtual void tick(EntityManager* em, float32 dt) {};
		};

		template<typename TSystem>
		class DRAUG_API System : public BaseSystem {
		};

		class SystemManager {
			EntityManager* m_entity_mgr;
			std::vector<BaseSystem*> m_systems;

		public:
			SystemManager(EntityManager* em) : m_entity_mgr(em) {
			}
			~SystemManager() {
				while (m_systems.empty() == false) {
					delete m_systems.back();
					m_systems.pop_back();
				}
			}

			template<typename TSystem>
			inline void addSystem(TSystem* s) {
				m_systems.push_back(s);
			}

			template<typename TSystem, typename... Args>
			inline void addSystem(Args&& ... args) {
				TSystem* s = new TSystem(std::forward(args)...);
				return addSystem(s);
			}

			void tick(float32 dt) {
				for (size_t i = 0; i < m_systems.size(); i++) {
					m_systems[i]->tick(m_entity_mgr, dt);
				}
			}
		};
	}
}
