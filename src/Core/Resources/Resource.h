#pragma once

#include "Core/Types.h"

namespace Draug {

struct ResourceType {
	uint32 type_hash;

	ResourceType() = delete;
	ResourceType(const char* name) :
		type_hash(calc_hash(name)) {
	}

private:
	// https://en.wikipedia.org/wiki/PJW_hash_function
	inline uint32 calc_hash(const char* s) {
		uint32 h = 0, high;
		while (*s) {
			h = (h << 4) + *s++;
			if (high = h & 0xF0000000) {
				h ^= high >> 24;
			}
			h &= ~high;
		}
		return h;
	}
};

#define RESOURCE_TYPE(type_name) virtual ResourceType getType() const override { static ResourceType type(type_name); return type; }

enum ResourceState : uint32 {
	None = 0,
	Initializing,
	Ready,
	Failed,
};

class Resource {
public:

	inline bool isValid() const { return m_state != ResourceState::None && m_state != ResourceState::Failed; }
	inline bool isInitializing() const { return m_state == ResourceState::Initializing; }
	inline bool isReady() const { return m_state == ResourceState::Ready; }
	inline bool failed() const { return m_state == ResourceState::Failed; }
	inline ResourceState getState() const { return m_state; }

	virtual ResourceType getType() const = 0;

private:
	ResourceState m_state;
};

}
