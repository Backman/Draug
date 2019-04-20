#include "draugpch.h"
#include "SFMLWindowImpl.h"
#include "Core/Types.h"
#include "Core/Window/WindowConfig.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

namespace Draug {
namespace details {
void closeAndDeleteWindow(sf::RenderWindow* window) {
	if (window == nullptr) {
		return;
	}
	window->close();
	delete window;
	window = nullptr;
}

SFMLWindowImpl::~SFMLWindowImpl() {
}

void SFMLWindowImpl::initialize(const Draug::WindowConfig& config) {
	sf::VideoMode videoMode(config.width, config.height);
	sf::ContextSettings contextSettings;

	uint32 windowStyle = sf::Style::Default;
	if (config.fullscreen) {
		windowStyle |= sf::Style::Fullscreen;
	}

	if (window == nullptr) {
		window = new sf::RenderWindow(videoMode, config.title, windowStyle, contextSettings);
	}
	else {
		window->close();
		window->create(videoMode, config.title, windowStyle, contextSettings);
	}
}

void SFMLWindowImpl::update() {
	window->display();
	BaseWindowImpl::update();
}

void SFMLWindowImpl::processEvents() {
	sf::Event sf_event;
	while (window->pollEvent(sf_event)) {
		switch (sf_event.type) {
			case sf::Event::Closed:
			{
				WindowCloseEvent evt;
				dispatchEvent(evt);
				//m_pending_events.emplace_back(evt);
			}
			break;
			case sf::Event::Resized:
			{
				WindowResizeEvent evt;
				evt.width = sf_event.size.width;
				evt.height = sf_event.size.height;
				dispatchEvent(evt);
				//m_pending_events.emplace_back(evt);
			}
			break;
			default:
				break;
		}
	}
	BaseWindowImpl::processEvents();
}

void SFMLWindowImpl::shutdown() {
	closeAndDeleteWindow(window);
	BaseWindowImpl::shutdown();
}
}
}