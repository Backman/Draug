#pragma once

#include "Draug.h"

namespace Draug {

struct EmptyConfig {};

template<typename T>
struct ResourceConfig {
	using Type = EmptyConfig;
};

template<typename T>
class ResourceManager {
public:
	using Config = typename ResourceConfig<T>::Type;
	using Loader = std::function<void(T&, const std::string&, const Config&)>;
	using Init = std::function<void(T&)>;

	void init(const std::string& resource_path);
	void init(const std::string& resource_path, Loader loader);

	T& create(const std::string& name);
	T& create(const std::string& name, Init init);

	T* get(const std::string& name);
	T* load(const std::string& name);
	T* load(const std::string& name, const Config& config);
	T* load(const std::string& path, const std::string& name);
	T* load(const std::string& path, const std::string& name, const Config& config);
	void remove(const std::string& name);

	void clear();

	bool exists(const std::string& name);

private:
	Loader m_loader;
	std::string m_resource_path;
	std::unordered_map<std::string, T*> m_assets;
};

template<typename T>
inline void ResourceManager<T>::init(const std::string& resource_path) {
	m_resource_path = resource_path;
}

template<typename T>
inline void ResourceManager<T>::init(const std::string& resource_path, Loader loader) {
	m_resource_path = resource_path;
	m_loader = loader;
}

template<typename T>
inline T& ResourceManager<T>::create(const std::string& name) {
	if (exists(name)) {
		remove(name);
	}
	m_assets[name] = new T();
	return *m_assets[name];
}

template<typename T>
inline T& ResourceManager<T>::create(const std::string& name, Init init) {
	T& resource = create(name);
	init(resource);
	return resource;
}

template<typename T>
inline T* ResourceManager<T>::get(const std::string& name) {
	if (exists(name) == false) {
		return nullptr;
	}
	return m_assets[name];
}

template<typename T>
inline T* ResourceManager<T>::load(const std::string& name) {
	return load(name, Config{});
}

template<typename T>
inline T* ResourceManager<T>::load(const std::string& name, const Config& config) {
	if (exists(name)) {
		return m_assets[name];
	}
	std::string full_path = Gfx::get().get_full_path(m_resource_path + "/" + name);
	if (full_path.empty()) {
		return nullptr;
	}

	T& resource = create(name);
	m_loader(resource, full_path, config);
	m_assets[name] = &resource;
	return m_assets[name];
}

template<typename T>
inline T* ResourceManager<T>::load(const std::string& path, const std::string& name) {
	return load(path, name, {});
}

template<typename T>
inline T* ResourceManager<T>::load(const std::string& path, const std::string& name, const Config& config) {
	if (exists(name)) {
		return m_assets[name];
	}
	T& resource = create(name);
	m_loader(resource, path + "/" + name, config);
	m_assets[name] = &resource;
	return m_assets[name];
}

template<typename T>
inline void ResourceManager<T>::remove(const std::string& name) {
	if (exists(name) == false) {
		return;
	}
	delete m_assets[name];
	m_assets[name] = nullptr;
}

template<typename T>
inline void ResourceManager<T>::clear() {
	for (auto const& asset : m_assets) {
		remove(asset.first);
	}
	m_assets.clear();
}

template<typename T>
inline bool ResourceManager<T>::exists(const std::string& name) {
	return m_assets.find(name) != m_assets.end();
}
}
