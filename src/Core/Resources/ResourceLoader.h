#pragma once

#include "draugpch.h"
#include "Core/Types.h"

namespace Draug {
namespace Resources {


class BaseResourceLoader {
	static uint32 s_id;
};

template<typename T>
class ResourceLoader {
	typedef std::function<T*> LoaderFn;
	LoaderFn m_loader;

public:
	ResourceLoader() = delete;
	ResourceLoader(const ResourceLoader& other) = delete;
	~ResourceLoader() = default;

	inline T* load() {
		return m_loader_fn();
	}

	inline static ResourceLoader create(LoaderFn loader_fn) {
		m_loader = loader_fn;
	}
};

#ifdef DRAUG_SFML
template<typename T, typename... Args>
ResourceLoader<T> fromFile(const std::string& path, Args&&... args) {
	return ResourceLoader<T>::create([=](R & resource)
		{
			T* resource = new T();
			t->loadFromFile(path, args...);
			return t;
		});
}
#endif

}
}
