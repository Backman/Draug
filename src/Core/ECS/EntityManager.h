#pragma once

#include "draugpch.h"
#include "Types.h"
#include "Component.h"

namespace Draug {
	namespace ECS {
		struct DRAUG_API Entity {
		public:
			EntityId id;
			inline uint64 index() const { return id & details::ENTITY_INDEX_MASK; }
			inline uint64 generation() const { return (id >> details::ENTITY_INDEX_BITS) & details::ENTITY_GENERATION_MASK; }
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
					uint64 index;

					bool operator==(const Iterator& rhs) const { return index == rhs.index; }
					bool operator!=(const Iterator& rhs) const { return (*this == rhs) == false; }

					Iterator& operator++() {
						index++;
						nextIndex();
						return *this;
					}

					value_type operator*() { return entity_mgr->create(index); }
					const value_type operator*() const { return entity_mgr->create(index); }

					void nextIndex() {
						while (index < entity_mgr->getCapacity() && (entity_mgr->m_component_masks[index] & component_mask) != component_mask) {
							index++;
						}
					}
				};

				EntityManager* entity_mgr;
				ComponentMask component_mask;

				Iterator begin() {
					Iterator it = Iterator{ entity_mgr, component_mask, 0 };
					it.nextIndex();
					return it;
				}
				Iterator end() { return Iterator{ entity_mgr, component_mask, entity_mgr->getCapacity() }; }
			};
		public:
			EntityManager() {
			}

			inline Entity create() {
				uint64 index;
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
			inline Entity create(Args&&... args) {
				Entity e = create();
				addComponent<T>(e, args...);
				return e;
			}

			inline void create(uint32 count) {
				for (size_t i = 0; i < count; i++) {
					create();
				}
			}

			template<typename T, typename... Args>
			inline void create(uint32 count, Args&&... args) {
				for (size_t i = 0; i < count; i++) {
					create<T>(args...);
				}
			}

			inline void destroy(const Entity& e) {
				const uint64 index = e.index();
				m_generations[index]++;
				m_free_list.emplace_back(index);
			}

			inline bool isAlive(const Entity& e) const {
				const uint64 index = e.index();
				return index < m_generations.size() && m_generations[index] == e.generation();
			}

			inline size_t getCapacity() const { return m_component_masks.size(); }
			inline size_t getAliveCount() const { return m_component_masks.size() - m_free_list.size(); }

			template<typename TComponent>
			inline TComponent& getComponent(const Entity& e) {
				return Component<TComponent>::getInstance(e.index());
			}

			template<typename TComponent>
			inline void addComponent(const Entity& e, TComponent c) {
				m_component_masks[e.index()].set(Component<TComponent>::getId());
			}

			template<typename TComponent, typename... Args>
			inline void addComponent(const Entity& e, Args && ... args) {
				TComponent& c = Component<TComponent>::createInstance(e.index(), args...);
				addComponent<TComponent>(e, c);
			}

			template<typename TComponent>
			inline void removeComponent(const Entity& e) {
				m_component_masks[e.index()].reset(Component<TComponent>::getId());
			}

			template<typename TComponent>
			inline bool hasComponent(const Entity& e) const {
				return m_component_masks[e.index()].test(Component<TComponent>::getId());
			}

			inline ComponentMask getComponentMask(const Entity& e) const {
				return m_component_masks[e.index()];
			}

			template<typename TComponent>
			inline ComponentMask getComponentMask() {
				ComponentMask mask;
				mask.set(Component<TComponent>::getId());
				return mask;
			}

			template<typename TComponent1, typename TComponent2, typename ...TComponents>
			inline ComponentMask getComponentMask() {
				return getComponentMask<TComponent1>() | getComponentMask<TComponent2, TComponents...>();
			}

			template<typename... TComponents>
			inline EntityCollection entities() {
				return EntityCollection{ this, getComponentMask<TComponents...>() };
			}
		private:
			inline Entity create(uint64 index) {
				return Entity { index | (m_generations[index] << details::ENTITY_INDEX_BITS) };
			}

			std::vector<uint64> m_entities;
			std::vector<uint64> m_generations;
			std::vector<uint64> m_free_list;
			std::vector<ComponentMask> m_component_masks;
		};
	}
}
