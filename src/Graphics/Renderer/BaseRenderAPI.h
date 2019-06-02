#pragma once

namespace Draug {
class Window;

class BaseRenderAPI {
public:
	BaseRenderAPI() = default;
	virtual ~BaseRenderAPI() = default;

	virtual void init(Window* window) = 0;
	virtual void shutdown() = 0;

	virtual void begin_frame() = 0;
	virtual void render_frame() = 0;
	virtual void end_frame() = 0;

	virtual void reset() = 0;
};
}
