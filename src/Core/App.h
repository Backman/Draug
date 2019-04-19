#pragma once

#include "Draug.h"
#include "Resources/ResourceManager.h"
#include <SFML/Graphics/Image.hpp>

namespace Draug {
class DRAUG_API App {
public:
	Resources::ResourceManager<sf::Image> images;
	App() = default;
	App(const App& other) = default;
	virtual ~App();

	virtual void initialize();
	virtual void run();
	virtual void shutdown();
};

App* createApp();
}
