#pragma once

#include <bitset>
#include <unordered_map>
#include <vector>
#include "Types.h"

namespace Draug {
	namespace ECS {
		template<typename TComponent>
		struct DRAUG_API Component {
			inline static ComponentId getId() {
				static ComponentId id = m_id++;
				return id;
			}

			static inline TComponent& getInstance(const uint64 index) {
				ComponentId id = Component<TComponent>::getId();
				validateComponent(id, index);
				return m_component_pool[id][index];
			}

			template<typename... Args>
			static inline TComponent& createInstance(const uint64 index, Args&& ... args) {
				ComponentId id = Component<TComponent>::getId();
				validateComponent(id, index);
				m_component_pool[id][index] = TComponent{ std::forward<Args>(args)... };
				return m_component_pool[id][index];
			}
		private:
			static inline void validateComponent(const ComponentId id, const uint64 index) {
				if (m_component_pool.find(id) == m_component_pool.end()) {
					m_component_pool[id] = std::vector<TComponent>();
				}
				if (m_component_pool[id].size() <= index) {
					m_component_pool[id].resize(index + 1);
				}
			}
			static ComponentId m_id;
			static std::unordered_map<ComponentId, std::vector<TComponent>> m_component_pool;
		};

		template<typename TComponent>
		ComponentId Component<TComponent>::m_id = 0;
		template<typename TComponent>
		std::unordered_map<ComponentId, std::vector<TComponent>> Component<TComponent>::m_component_pool;
	}
}
