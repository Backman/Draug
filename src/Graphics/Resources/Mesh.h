#pragma once

#include "Draug.h"
#include <bgfx/bgfx.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Draug {
struct PosColVertex {
	glm::vec3 m_pos;
	glm::vec4 m_color;

	static bgfx::VertexDecl s_decl;
	void static init();
};

class Mesh {
public:
	static Mesh* s_quad;
	static Mesh* s_triangle;
	void static init();

	static Mesh* create(const PosColVertex* vertices, int vertex_count, const unsigned int* indices, int index_count);

	void bind(unsigned int bgfx_stream);

	bgfx::VertexBufferHandle m_vertex_buffer;
	bgfx::IndexBufferHandle m_index_buffer;

private:
	void setup();

	unsigned int m_vertex_count = 0;
	unsigned int m_index_count = 0;
	int m_submesh_count = 1;

	PosColVertex* m_vertices;
	unsigned int* m_indices;
};
}
