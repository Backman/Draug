#pragma once

#include "Core/Window/WindowImpl/BaseWindowImpl.h"

namespace sf {
class RenderWindow;
}

namespace Draug {
namespace details {
class SFMLWindowImpl : public BaseWindowImpl {
public:
	sf::RenderWindow* window;

	SFMLWindowImpl() = default;
	SFMLWindowImpl(const SFMLWindowImpl& other) = delete;
	~SFMLWindowImpl();

	void initialize(const Draug::WindowConfig& config) override;
	void update() override;
	void processEvents() override;
	void shutdown() override;
};
}
}
