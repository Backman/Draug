#pragma once

#include "Draug.h"
#include "Types.h"
#include "Component.h"

namespace Draug {
namespace OLD_ECS {
struct DRAUG_API Entity {
public:
	EntityId id;
	inline size_t index() const { return id & details::ENTITY_INDEX_MASK; }
	inline size_t generation() const { return (id >> details::ENTITY_INDEX_BITS) & details::ENTITY_GENERATION_MASK; }
};

class DRAUG_API EntityManager {
public:
	struct EntityCollection {
		struct Iterator {
			using value_type = Entity;
			using reference = value_type &;
			using pointer = value_type *;
			using difference_type = size_t;
			using iterator_category	= std::forward_iterator_tag;

			EntityManager* entity_mgr;
			ComponentMask component_mask;
			size_t index;

			bool operator==(const Iterator& rhs) const { return index == rhs.index; }
			bool operator!=(const Iterator& rhs) const { return (*this == rhs) == false; }

			Iterator& operator++() {
				index++;
				next_index();
				return *this;
			}

			value_type operator*() { return entity_mgr->create(index); }
			const value_type operator*() const { return entity_mgr->create(index); }

			void next_index() {
				while (index < entity_mgr->get_capacity() && (entity_mgr->m_component_masks[index] & component_mask) != component_mask) {
					index++;
				}
			}
		};

		EntityManager* entity_mgr;
		ComponentMask component_mask;

		Iterator begin() {
			Iterator it = Iterator{ entity_mgr, component_mask, 0 };
			it.next_index();
			return it;
		}
		Iterator end() { return Iterator{ entity_mgr, component_mask, entity_mgr->get_capacity() }; }
	};
public:
	EntityManager() {
	}

	inline void init() {
	}

	inline Entity create() {
		size_t index;
		if (m_free_list.empty() == false) {
			index = m_free_list.back();
			m_free_list.pop_back();
		}
		else {
			m_generations.emplace_back(0);
			index = m_generations.size() - 1;
			if (m_component_masks.size() <= index) {
				m_component_masks.resize(index + 1);
			}
		}

		return create(index);
	}

	template<typename T, typename... Args>
	inline Entity create(Args && ... args) {
		Entity e = create();
		add_component<T>(e, args...);
		return e;
	}

	inline void create(int count) {
		for (size_t i = 0; i < count; i++) {
			create();
		}
	}

	template<typename T, typename... Args>
	inline void create(int count, Args && ... args) {
		for (size_t i = 0; i < count; i++) {
			create<T>(args...);
		}
	}

	inline void destroy(const Entity & e) {
		const size_t index = e.index();
		m_generations[index]++;
		m_free_list.emplace_back(index);
	}

	inline bool isAlive(const Entity & e) const {
		const size_t index = e.index();
		return index < m_generations.size() && m_generations[index] == e.generation();
	}

	inline size_t get_capacity() const { return m_component_masks.size(); }
	inline size_t get_alive_count() const { return m_component_masks.size() - m_free_list.size(); }

	template<typename TComponent>
	inline TComponent& get_component(const Entity & e) {
		return Component<TComponent>::get(e.index());
	}

	template<typename TComponent>
	inline void add_component(const Entity & e, TComponent c) {
		m_component_masks[e.index()].set(Component<TComponent>::get_id());
	}

	template<typename TComponent, typename... Args>
	inline void add_component(const Entity & e, Args && ... args) {
		TComponent& c = Component<TComponent>::create(e.index(), args...);
		add_component<TComponent>(e, c);
	}

	template<typename TComponent>
	inline void remove_component(const Entity & e) {
		m_component_masks[e.index()].reset(Component<TComponent>::get_id());
	}

	template<typename TComponent>
	inline bool has_component(const Entity & e) const {
		return m_component_masks[e.index()].test(Component<TComponent>::get_id());
	}

	inline ComponentMask get_component_mask(const Entity & e) const {
		return m_component_masks[e.index()];
	}

	template<typename TComponent>
	inline ComponentMask get_component_mask() {
		ComponentMask mask;
		mask.set(Component<TComponent>::get_id());
		return mask;
	}

	template<typename TComponent1, typename TComponent2, typename ...TComponents>
	inline ComponentMask get_component_mask() {
		return get_component_mask<TComponent1>() | get_component_mask<TComponent2, TComponents...>();
	}

	template<typename... TComponents>
	inline EntityCollection entities() {
		return EntityCollection{ this, get_component_mask<TComponents...>() };
	}
private:
	inline Entity create(size_t index) {
		return Entity{ index | (m_generations[index] << details::ENTITY_INDEX_BITS) };
	}

	std::vector<size_t> m_entities;
	std::vector<size_t> m_generations;
	std::vector<size_t> m_free_list;
	std::vector<ComponentMask> m_component_masks;
};
}
}
