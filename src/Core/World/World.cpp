#include "World.h"
#include "Core/App/App.h"

namespace Draug {
World::~World() {
	shutdown();
}

void World::init(App* app) {
	m_entity_mgr = new OLD_ECS::EntityManager();
	m_entity_mgr->init();
	m_system_mgr = new OLD_ECS::SystemManager();
	m_system_mgr->init(OLD_ECS::SystemContext{ this, app });
	m_app = app;
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

void World::tick(float dt) {
	m_system_mgr->tick(dt);
}

void World::fixed_tick(float fixed_dt) {
	m_system_mgr->fixed_tick(fixed_dt);
}

OLD_ECS::Entity World::create_entity() {
	return m_entity_mgr->create();
}

void World::create_entities(int count) {
	m_entity_mgr->create(count);
}
}