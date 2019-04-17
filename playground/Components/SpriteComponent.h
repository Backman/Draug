#pragma once

#include <string>


struct SpriteComponent {
	std::string filename;
private:
	friend std::ostream& operator<<(std::ostream& lhs, const SpriteComponent& rhs);
};

std::ostream& operator<<(std::ostream& lhs, const SpriteComponent& rhs) {
	lhs << "PositionComponent (" << rhs.filename << ")";
	return lhs;
}
