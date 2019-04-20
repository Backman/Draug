#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>

struct SpriteComponent {
	sf::Texture* texture;
	sf::Color color = sf::Color::White;
	bool is_dirty = true;
};
