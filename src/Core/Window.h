#pragma once

#include "Core/WindowConfig.h"

namespace Draug {
	namespace details {
		class WindowImpl;
	}
	class Window {
		details::WindowImpl* s_window_impl;
	public:
		WindowConfig config;

		Window();
		~Window();


		void initialize(const WindowConfig& config);
		void display();
		void shutdown();
	};
}
