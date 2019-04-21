#pragma once

#include "Draug.h"
#include "ResourceLoader.h"

namespace Draug {
template<typename T, typename Id>
class ResourceManager {
public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager& other) = delete;
	~ResourceManager() = default;

	void initialize() {
	}

	template<typename... Args>
	inline T& get(const Id& id, ResourceLoader<T> loader) {
		auto it = m_resources.find(id);
		if (it == m_resources.end()) {
			return load(id, loader);
		}
		return *it->second;
	}

	inline void release(const Id& id) {
		if (m_resources.find(id) == m_resources.end()) {
			return;
		}
		T* resource = m_resources.at(id);
		delete resource;
		resource = nullptr;
		m_resources.erase(id);
	}

	inline void releaseAll() {
		for (auto it = m_resources.begin(); it != m_resources.end();) {
			if (it->second != nullptr) {
				T* ptr = it->second;
				it = m_resources.erase(it);
				delete ptr;
			}
			else {
				it++;
			}
		}
	}

private:
	inline T& load(const Id& id, ResourceLoader<T> loader) {
		T* resource = loader.load();
		m_resources.emplace(id, instance);
		return instance;
	}

	std::unordered_map<Id, T*> m_resources;
};
}