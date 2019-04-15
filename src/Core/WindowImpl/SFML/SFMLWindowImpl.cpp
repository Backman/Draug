#include "draugpch.h"
#include "SFMLWindowImpl.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace Draug {
	namespace details {
		sf::RenderWindow* SFMLWindowImpl::window = nullptr;

		SFMLWindowImpl::SFMLWindowImpl() {
		}
		SFMLWindowImpl::~SFMLWindowImpl() {
			shutdown();
		}

		void SFMLWindowImpl::initialize(const Draug::WindowConfig& config) {
			sf::VideoMode videoMode(config.width, config.height);
			sf::ContextSettings contextSettings;

			uint32 windowStyle;
			if (config.fullscreen) {
				windowStyle = sf::Style::Fullscreen;
			}

			window = new sf::RenderWindow(videoMode, config.title, windowStyle, contextSettings);
		}

		void SFMLWindowImpl::display() {
			window->display();
		}

		void SFMLWindowImpl::shutdown() {
			if (window == nullptr) {
				return;
			}
			window->close();
			delete window;
		}
	}
}