#pragma once

#include "Draug.h"
#include "Core/Types.h"

namespace Draug {
class BaseResourceLoader {
	static uint32 s_id;
};

template<typename T>
class ResourceLoader {
public:
	typedef std::function<T*> LoaderFn;

	ResourceLoader() = delete;
	ResourceLoader(const ResourceLoader& other) = delete;
	~ResourceLoader() = default;

	inline T* load() {
		return m_loader_fn();
	}

	inline static ResourceLoader create(LoaderFn loader_fn) {
		m_loader = loader_fn;
	}

private:
	LoaderFn m_loader;
};

}
