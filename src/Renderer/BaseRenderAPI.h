#pragma once

namespace Draug {
class Window;

class BaseRenderAPI {
public:
	BaseRenderAPI() = default;
	virtual ~BaseRenderAPI() = default;

	virtual void init(Window* window) = 0;
	virtual void shutdown() = 0;

	virtual void beginFrame() = 0;
	virtual void renderFrame() = 0;
	virtual void endFrame() = 0;
};
}
