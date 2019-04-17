#pragma once

#include "draugpch.h"

namespace Draug {
	namespace ECS {
		class Scene;
		class DRAUG_API System {
		public:
			virtual void init(Scene* scene) {}
			virtual void tick(Scene* scene, float32 dt) {}
			virtual void shutdown(Scene* scene) {}
		};

		class SystemManager {
			std::vector<System*> m_systems;
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

			void tick(Scene* scene, float32 dt) {
				for (size_t i = 0; i < m_systems.size(); i++) {
					m_systems[i]->tick(scene, dt);
				}
			}
		};
	}
}
