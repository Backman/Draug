#pragma once

#include <bitset>
#include "../Types.h"

namespace Draug {
	namespace ECS {
		namespace details {
			const uint32 ENTITY_INDEX_BITS = 32;
			const uint64 ENTITY_INDEX_MASK = (uint64(1) << ENTITY_INDEX_BITS) - 1;
			const uint64 ENTITY_GENERATION_MASK = (uint64(1) << ENTITY_INDEX_BITS) - 1;

			const uint32 MAX_COMPONENTS = 64;
		}
		typedef uint64 EntityId;
		typedef uint32 ComponentId;

		typedef std::bitset<details::MAX_COMPONENTS> ComponentMask;
	}
}
