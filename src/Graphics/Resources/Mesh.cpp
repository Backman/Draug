#include "Mesh.h"

namespace Draug {
bgfx::VertexDecl PosColVertex::s_decl;

void PosColVertex::init() {
	s_decl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float, true)
		.end();
}

static PosColVertex s_triangle_vertices[] = {
		{ glm::vec3 { -0.5f,  -0.5f, 0.0f }, glm::vec4 { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ glm::vec3 { 0.0f,  0.5f, 0.0f }, glm::vec4 { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ glm::vec3 { 0.5f,  -0.5f, 0.0f }, glm::vec4 { 0.0f, 0.0f, 1.0f, 1.0f } },
};

static PosColVertex s_quad_vertices[] = {
	{ glm::vec3 { 0.5f,  0.5f, 0.0f }, glm::vec4 { 1.0f, 0.0f, 0.0f, 1.0f } },
	{ glm::vec3 { 0.5f,  -0.5f, 0.0f }, glm::vec4 { 0.0f, 1.0f, 0.0f, 1.0f } },
	{ glm::vec3 { -0.5f,  -0.5f, 0.0f }, glm::vec4 { 0.0f, 0.0f, 1.0f, 1.0f } },
	{ glm::vec3 { -0.5f,  0.5f, 0.0f }, glm::vec4 { 0.0f, 0.0f, 0.0f, 1.0f } },
};

static unsigned int s_triangle_indices[] = {
	0, 1, 2
};

static unsigned int s_quad_indices[] = {
	0, 1, 3,
	1, 2, 3
};

Mesh* Mesh::s_triangle = nullptr;
Mesh* Mesh::s_quad = nullptr;

void Mesh::init() {
	PosColVertex::init();

	s_triangle = Mesh::create(s_triangle_vertices, 3, s_triangle_indices, 3);
	s_quad = Mesh::create(s_quad_vertices, 4, s_quad_indices, 6);
}

void Mesh::setup() {
	m_vertex_buffer = bgfx::createVertexBuffer(bgfx::makeRef(m_vertices, sizeof(PosColVertex) * m_vertex_count), PosColVertex::s_decl);
	m_index_buffer = bgfx::createIndexBuffer(bgfx::makeRef(m_indices, sizeof(unsigned int) * m_index_count), BGFX_BUFFER_INDEX32);
}

Mesh* Mesh::create(const PosColVertex* vertices, int vertex_count, const unsigned int* indices, int index_count) {
	Mesh* mesh = new Mesh();

	mesh->m_vertex_count = vertex_count;
	mesh->m_vertices = new PosColVertex[vertex_count];
	mesh->m_indices = new unsigned int[index_count];
	mesh->m_index_count = index_count;

	for (int i = 0; i < vertex_count; ++i) {
		mesh->m_vertices[i] = vertices[i];
	}

	for (int i = 0; i < index_count; ++i) {
		mesh->m_indices[i] = indices[i];
	}
	mesh->setup();
	
	return mesh;
}

void Mesh::bind(unsigned int bgfx_stream) {
	bgfx::setVertexBuffer(bgfx_stream, m_vertex_buffer);
	bgfx::setIndexBuffer(m_index_buffer);
}
}
