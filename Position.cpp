#include "Position.h"


Position::Position() {
	_currentX = 918;
	_currentY = 200;
}

sf::Vector2f Position::get_current_position() {
	return sf::Vector2f(_currentX, _currentY);
}



void Position::move(DIRECTION dir) {
	switch (dir) {
		case Position::RIGHT: {
			if (_currentX < 1206) { _currentX += 32; }
			break;
		}
		case Position::DOWN: {
			if (_currentY < 488) { _currentY += 32; }
			break;
		}
		case Position::UP: {
			if (_currentY > 200) { _currentY -= 32; }
			break;
		}
		case Position::LEFT: {
			if (_currentX > 918) { _currentX -= 32; }
			break;
		}
	}
}