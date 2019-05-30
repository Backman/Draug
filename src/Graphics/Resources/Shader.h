#pragma once

#include "Draug.h"
#include "Resource.h"
#include "ResourceManager.h"
#include <bx/file.h>
#include <bx/allocator.h>

namespace Draug {
class Shader : public ResourceHandle<ShaderHandle> {
public:
	Shader() = default;
	~Shader() = default;

	void load(bx::FileReaderI& reader, const std::string& name);

	std::string m_name;
};

class ShaderManager : public ResourceManager<Shader> {
};
}
