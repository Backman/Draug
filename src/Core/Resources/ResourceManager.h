#pragma once

#include "draugpch.h"

namespace Draug {
namespace Resources {
template<typename T>
class ResourceManager {
	std::unordered_map<std::string, T*> m_resources;
public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager& other) = delete;
	~ResourceManager() = default;

	template<typename... Args>
	inline T& get(const std::string& filename) {
		auto it = m_resources.find(filename);
		if (it == m_resources.end()) {
			return load(filename);
		}
		return *it->second;
	}

	inline void release(const std::string& filename) {
		if (m_resources.find(filename) == m_resources.end()) {
			return;
		}

		T* resource = m_resources.at(filename);
		delete resource;
		resource = nullptr;
		m_resources.erase(filename);
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
	inline T& load(const std::string& filename) {
		T* instance = new T();
		instance->loadFromFile(filename);
		m_resources.emplace(filename, instance);
		return *instance;
	}
};
}
}