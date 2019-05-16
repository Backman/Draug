#pragma once

#include "Draug.h"
#include "Types.h"

namespace Draug {
namespace ECS {
template<typename TComponent>
struct DRAUG_API Component {
	inline static ComponentId get_id() {
		static ComponentId id = s_id++;
		return id;
	}

	static inline TComponent& get(const size_t index) {
		ComponentId id = Component<TComponent>::get_id();
		validate(id, index);
		return s_component_pool[id][index];
	}

	template<typename... Args>
	static inline TComponent& create(const size_t index, Args&& ... args) {
		ComponentId id = Component<TComponent>::get_id();
		validate(id, index);
		s_component_pool[id][index] = TComponent{ std::forward<Args>(args)... };
		return s_component_pool[id][index];
	}
private:
	static inline void validate(const ComponentId id, const size_t index) {
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
