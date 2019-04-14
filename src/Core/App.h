#pragma once

#include "Draug.h"

namespace Draug {
	class DRAUG_API App {
	public:
		App() = default;
		virtual ~App() = default;

		virtual void initialize();
		virtual void run();
		virtual void shutdown();
	};

	App* createApp();
}
