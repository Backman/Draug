#pragma once
#include "Draug.h"
#include "Resource.h"
#include "ResourceHandle.h"
#include <bgfx/bgfx.h>

namespace Draug {

class ShaderProgram : public ResourceHandle<ProgramHandle> {
public:
	ShaderProgram(const std::string& name);
	~ShaderProgram();

	std::string m_name;
};
}
