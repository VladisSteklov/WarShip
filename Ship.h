#pragma once
#include <SFML\Graphics.hpp>
const int ships_constArr[10] = { 4,3,3,2,2,2,1,1,1,1 };

class Ship {
public:
	enum SHIP_TYPE
	{
		SINGLE,
		DOUBLE,
		TRIPLE,
		QUAD
	};

	enum DIRECTION
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	enum POSITION_TYPE
	{
		VERTICAL,
		GORIZONTAL
	};

	Ship();
	sf::Vector2f get_current_position();
	void move(DIRECTION);

	POSITION_TYPE& reverse();
	SHIP_TYPE& get_ship_type();
	POSITION_TYPE& get_position_type();

	void setPositionType(POSITION_TYPE);
	void setPosition(const float& ,const float&);
	
private:
	DIRECTION _dir;
	POSITION_TYPE _posType;
	SHIP_TYPE _shipType;
	float _currentX, _currentY;
};

