#pragma once

#include "Core/Window.h"

namespace Draug {
	namespace details {
		class IWindowImpl {
		public:
			IWindowImpl() {}
			virtual ~IWindowImpl() {}

			virtual void initialize(const WindowConfig& config) = 0;
			virtual void display() = 0;
			virtual void shutdown() = 0;
		};
	}
}
