#pragma once

#include "draugpch.h"
#include "Core/Window/WindowConfig.h"
#include "Core/Event/Event.h"

namespace Draug {
	namespace details {
		class WindowImpl;
	}
	class Window {
		details::WindowImpl* m_impl;
		std::vector<Event> m_pending_events;
	public:
		WindowConfig config;

		Window();
		~Window();


		void initialize(const WindowConfig& config);
		void update();
		void shutdown();

		EventHandlerId registerEventHandler(EventHandler handler);
		void unregisterEventHandler(EventHandlerId id);
	};
}
