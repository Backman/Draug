#pragma once

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include "ISystem.h";

namespace Draug {
namespace ECS {
using entity = entt::entity;
using registry = entt::registry;
using dispatcher = entt::dispatcher;
}
}
