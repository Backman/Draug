#include "World.h"
#include "Core/App/App.h"

namespace Draug {
World::~World() {
	shutdown();
}

void World::initialize(App* app) {
	m_entity_mgr = new ECS::EntityManager();
	m_entity_mgr->init();
	m_system_mgr = new ECS::SystemManager();
	m_system_mgr->init(ECS::SystemContext{ this, app });
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

void World::fixedTick() {
	m_system_mgr->fixedTick();
}

ECS::Entity World::createEntity() {
	return m_entity_mgr->create();
}

void World::createEntities(int count) {
	m_entity_mgr->create(count);
}
}