#pragma once

#include "Core/ECS/ISystem.h"
#include "Core/ECS/Components/PositionComponent.h"
#include "Core/ECS/Components/MeshComponent.h"
#include "Core/ECS/Components/RenderStateComponent.h"
#include "Graphics/Resources/ResourceUtils.h"
#include "Graphics/Gfx.h"

namespace Draug {
namespace ECS {
class MeshRenderSystem : public ISystem {
public:
	ProgramHandle m_program;
	bx::FileReader m_reader;

	virtual void init(World* world) override {
		Gfx& gfx = Gfx::get();
		m_program = load_shader_program(&m_reader, gfx.resource_path() + "/shaders/compiled/simple");
	}

	virtual void tick(float dt, World * world) {
		Window* window = world->app->get_window();
		const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };

		// Set view and projection matrix for view 0.
		float view_matrix[16];
		bx::mtxLookAt(view_matrix, eye, at);

		float proj_matrix[16];
		bx::mtxProj(proj_matrix,
			60.0f,
			float(window->get_width()) / float(window->get_height()),
			0.1f, 100.0f,
			bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewTransform(window->get_id(), view_matrix, proj_matrix);

		// Set view 0 default viewport.
		bgfx::setViewRect(window->get_id(), 0, 0,
			window->get_width(), window->get_height());

		auto rs_view = world->ecs.view<RenderStateComponent>();
		for (auto e : rs_view) {
			glm::vec3 cam_pos{ 0.0f, 0.0f, -10.0f };
			RenderStateComponent& render_state = world->ecs.get<RenderStateComponent>(e);
			bgfx::setUniform(render_state.m_camera_pos_uniform, &cam_pos);
			break;
		}

		auto view = world->ecs.view<PositionComponent, MeshComponent>();
		for (auto e : view) {
			auto comps = view.get<PositionComponent, MeshComponent>(e);
			PositionComponent& position = std::get<0>(comps);
			MeshComponent& mesh = std::get<1>(comps);

			float mtx[16];
			bx::mtxRotateY(mtx, 0.0f);

			// position x,y,z
			mtx[12] = -(position.x / (float)window->get_width());
			mtx[13] = -(position.y / (float)window->get_height());
			mtx[14] = 0.0f;

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and index buffer.
			mesh.instance->bind(0);

			// Set render states.
			bgfx::setState(BGFX_STATE_DEFAULT);

			// Submit primitive for rendering to view 0.
			bgfx::submit(window->get_id(), m_program);

		}
	}
};
}
}
