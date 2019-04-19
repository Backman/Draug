#include "draugpch.h"
#include "Scene.h"
#include "Core/App.h"

namespace Draug {
namespace ECS {
Scene::~Scene() {
	shutdown();
}

void Scene::initialize(App* app) {
	m_app = app;
	m_entity_mgr = new EntityManager();
	m_system_mgr = new SystemManager();
}

void Scene::shutdown() {
	if (m_entity_mgr != nullptr) {
		delete m_entity_mgr;
	}
	if (m_system_mgr != nullptr) {
		delete m_system_mgr;
	}
	m_entity_mgr = nullptr;
	m_system_mgr = nullptr;
}

void Scene::update() {
	m_system_mgr->tick(this, 0);
}
Entity Scene::createEntity() {
	return m_entity_mgr->create();
}
void Scene::createEntities(uint32 count) {
	m_entity_mgr->create(count);
}
}
}