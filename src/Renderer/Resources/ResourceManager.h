#pragma once

#include "Draug.h"

namespace Draug {
template<typename T>
class ResourceManager {
public:
	using ResourceLoader = std::function<void(T&, const std::string&)>;

	void set_loader(ResourceLoader loader);

	T& create(const std::string& name);
	T* get(const std::string& name);
	T* load(const std::string& path, const std::string& name);
	T* remove(const std::string& name);
	void clear();

private:
	ResourceLoader m_loader;
	std::unordered_map<std::string, T*> m_assets;
};

template<typename T>
inline void ResourceManager<T>::set_loader(ResourceLoader loader) {
	m_loader = loader;
}

template<typename T>
inline T& ResourceManager<T>::create(const std::string& name) {
	m_assets[name] = new T();
	return *m_assets[name];
}

template<typename T>
inline T* ResourceManager<T>::get(const std::string& name) {
	if (m_assets.find(name) == m_assets.end()) {
		return nullptr;
	}
	return m_assets[name];
}

template<typename T>
inline T* ResourceManager<T>::load(const std::string& path, const std::string& name) {
	if (m_assets.find(name) != m_assets.end()) {
		return m_assets[name];
	}
	T& resource = create(name);
	m_loader(resource, path + "/" + name);
	m_assets[name] = &resource;
	return m_assets[name];
}

template<typename T>
inline T* ResourceManager<T>::remove(const std::string& name) {
	m_assets[name] = nullptr;
}

template<typename T>
inline void ResourceManager<T>::clear() {
	m_assets.clear();
}
}
