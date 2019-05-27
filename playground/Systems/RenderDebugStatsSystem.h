#pragma once

#include <bgfx/bgfx.h>
#include <Core/ECS/World.h>
#include <Core/ECS/ISystem.h>
#include <Core/Event/Event.h>
#include <Input/Input.h>
#include "Components/DebugStatsComponent.h"

using namespace Draug::ECS;
using namespace Draug::Input;

class DebugTextSystem : public ISystem {
public:
	void tick(float dt, World* world) override {
		auto view = world->ecs.view<DebugStatsComponent>();
		for (entt::entity e : view) {
			DebugStatsComponent& debug = view.get(e);
			if (Input::keyboard.isKeyDown(Key::F1)) {
				debug.show_stats = !debug.show_stats;
			}
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
			bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
			bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
			bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
			const bgfx::Stats* stats = bgfx::getStats();
			bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.",
				stats->width, stats->height, stats->textWidth, stats->textHeight);
			bgfx::setDebug(debug.show_stats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
			break;
		}
	}
private:
};
