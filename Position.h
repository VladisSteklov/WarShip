#pragma once
#include <SFML\Graphics.hpp>

class Position {
public:

	enum DIRECTION
	{
		RIGHT,
		DOWN,
		UP,
		LEFT
	};

	Position();
	sf::Vector2f get_current_position();
	void move(DIRECTION);

private:
	float _currentX, _currentY;
};

