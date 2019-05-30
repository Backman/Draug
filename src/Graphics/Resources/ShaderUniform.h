#include "Draug.h"
#include "Resource.h"
#include "Resource.h"

namespace Draug {
struct ShaderUniform : public ResourceHandle<UniformHandle> {
	ShaderUniform() = default;

	void set_data(const std::string& name, UniformType type, unsigned int num);

	UniformInfo m_info;
};
}