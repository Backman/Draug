#include "draugpch.h"
#include "World.h"

namespace Draug {
	namespace ECS {
		World::~World() {
			shutdown();
		}

		void World::initialize() {
			m_entity_mgr = new EntityManager();
			m_system_mgr = new SystemManager(m_entity_mgr);
		}

		void World::shutdown() {
			if (m_entity_mgr != nullptr) {
				delete m_entity_mgr;
			}
			if (m_system_mgr != nullptr) {
				delete m_system_mgr;
			}
			m_entity_mgr = nullptr;
			m_system_mgr = nullptr;
		}

		void World::update() {
			m_system_mgr->tick(0);
		}
	}
}