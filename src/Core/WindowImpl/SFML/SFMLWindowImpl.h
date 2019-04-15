#pragma once

#include "Core/Window.h"
#include "Core/WindowImpl/IWindowImpl.h"

namespace sf {
	struct RenderWindow;
}

namespace Draug {
	namespace details {
		class SFMLWindowImpl : public IWindowImpl {
		public:
			static sf::RenderWindow* window;

			SFMLWindowImpl();
			~SFMLWindowImpl();

			void initialize(const Draug::WindowConfig& config) override;
			void display() override;
			void shutdown() override;
		};
	}
}
