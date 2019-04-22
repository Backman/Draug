#pragma once

#include "Draug.h"
#include "Types.h"

namespace Draug {
namespace ECS {
template<typename TComponent>
struct DRAUG_API Component {
	inline static ComponentId getId() {
		static ComponentId id = s_id++;
		return id;
	}

	static inline TComponent& getInstance(const uint64 index) {
		ComponentId id = Component<TComponent>::getId();
		validateComponent(id, index);
		return s_component_pool[id][index];
	}

	template<typename... Args>
	static inline TComponent& createInstance(const uint64 index, Args&& ... args) {
		ComponentId id = Component<TComponent>::getId();
		validateComponent(id, index);
		s_component_pool[id][index] = TComponent{ std::forward<Args>(args)... };
		return s_component_pool[id][index];
	}
private:
	static inline void validateComponent(const ComponentId id, const uint64 index) {
		if (s_component_pool.find(id) == s_component_pool.end()) {
			s_component_pool[id] = std::vector<TComponent>();
		}
		if (s_component_pool[id].size() <= index) {
			s_component_pool[id].resize(index + 1);
		}
	}
	static ComponentId s_id;
	static std::unordered_map<ComponentId, std::vector<TComponent>> s_component_pool;
};

template<typename TComponent>
ComponentId Component<TComponent>::s_id = 0;
template<typename TComponent>
std::unordered_map<ComponentId, std::vector<TComponent>> Component<TComponent>::s_component_pool;
}
}
