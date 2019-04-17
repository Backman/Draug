#pragma once

struct PositionComponent {
	int x, y;

private:
	friend std::ostream& operator<<(std::ostream& lhs, const PositionComponent& rhs);
};

std::ostream& operator<<(std::ostream& lhs, const PositionComponent& rhs) {
	lhs << "PositionComponent (" << rhs.x << ", " << rhs.y << ")";
	return lhs;
}
