#pragma once

#include "Draug.h"

namespace Draug {
namespace OLD_ECS {
namespace details {
const unsigned int ENTITY_INDEX_BITS = 32;
const size_t ENTITY_INDEX_MASK = (size_t(1) << ENTITY_INDEX_BITS) - 1;
const size_t ENTITY_GENERATION_MASK = (size_t(1) << ENTITY_INDEX_BITS) - 1;

const uint16_t MAX_COMPONENTS = 64;
}
typedef size_t EntityId;
typedef size_t ComponentId;

typedef std::bitset<details::MAX_COMPONENTS> ComponentMask;
}
}
