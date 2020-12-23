#include "Ship.h"

int numer_ship = 0;

Ship::Ship() {
	_currentX = 200;
	_currentY = 200;
	_dir = DIRECTION::RIGHT;
	_posType = POSITION_TYPE::GORIZONTAL;
	switch (ships_constArr[numer_ship]) {
		case 4: {
			_shipType = SHIP_TYPE::QUAD;
			break;
		}
		case 3: {
			_shipType = SHIP_TYPE::TRIPLE;
			break;
		}
		case 2: {
			_shipType = SHIP_TYPE::DOUBLE;
			break;
		}
		case 1: {
			_shipType = SHIP_TYPE::SINGLE;
			break;
		}
	}
	++numer_ship;
	if (numer_ship == 10)
		numer_ship = 0;
}



Ship::SHIP_TYPE& Ship::get_ship_type(){
	return _shipType;
}

Ship::POSITION_TYPE& Ship::get_position_type() {
	return _posType;
}

sf::Vector2f Ship::get_current_position() {
	return sf::Vector2f (_currentX, _currentY);
}

void Ship::move(DIRECTION dir) {
	switch (_posType) {
		case POSITION_TYPE::GORIZONTAL: {
			switch (dir)
			{
				case DIRECTION::RIGHT:
				{
					if ((_currentX < 392 && _shipType == SHIP_TYPE::QUAD) ||
						(_shipType == SHIP_TYPE::TRIPLE && _currentX < 424) ||
						(_shipType == SHIP_TYPE::DOUBLE && _currentX < 456) ||
						(_shipType == SHIP_TYPE::SINGLE && _currentX < 488)
						) {
						_currentX += 32; 
					}
					// 200 + i*32
					break;
				}
				case DIRECTION::LEFT:
				{
					if (_currentX > 200) 
						_currentX -= 32;
					break;
				}
				case DIRECTION::UP:
				{
					if (_currentY > 200) 
						_currentY -= 32;
					break;
				}
				case DIRECTION::DOWN:
				{
					if (_currentY < 488) //200 + 9*32
						_currentY += 32;
					break;
				}
			}
			break;
		}
	
		case POSITION_TYPE::VERTICAL: {
			switch (dir) {					
				case DIRECTION::RIGHT:
				{
					if (_currentX < 488)
						_currentX += 32; // 200 + i*32
					break;
				}
				case DIRECTION::LEFT:
				{
					if (_currentX > 200) 
						_currentX -= 32;
					break;
				}
				case DIRECTION::UP:
				{
					if (_currentY > 200) 
						_currentY -= 32;
					break;
				}
				case DIRECTION::DOWN:
				{
					if ((_currentY < 392 && _shipType == SHIP_TYPE::QUAD) ||
						(_shipType == SHIP_TYPE::TRIPLE && _currentY < 424) ||
						(_shipType == SHIP_TYPE::DOUBLE && _currentY < 456) ||
						(_shipType == SHIP_TYPE::SINGLE && _currentY < 488)
						) {
							_currentY += 32;
					}
					break;
				}
			}
			break;
		}
	}
	
}

void Ship::setPositionType(Ship::POSITION_TYPE POS_TYPE){
	_posType = POS_TYPE;
}



void Ship::setPosition(const float& x,const float& y){
	_currentX = x; _currentY = y;
}

Ship::POSITION_TYPE& Ship::reverse()
{
	switch (_posType) {
		case Ship::VERTICAL: {
			_posType = POSITION_TYPE::GORIZONTAL;
			if (_currentX >= 392 && _shipType == SHIP_TYPE::QUAD) { _currentX = 392; }
			if (_shipType == SHIP_TYPE::TRIPLE && _currentX >= 424) { _currentX = 424; }
			if (_shipType == SHIP_TYPE::DOUBLE && _currentX >= 456) { _currentX = 456; }
		
			break;
		}
		case Ship::GORIZONTAL: {
			_posType = POSITION_TYPE::VERTICAL;
			if (_currentY >= 392 && _shipType == SHIP_TYPE::QUAD) { _currentY = 392; }
			if (_shipType == SHIP_TYPE::TRIPLE && _currentY >= 424) { _currentY = 424; }
			if (_shipType == SHIP_TYPE::DOUBLE && _currentY >= 456) { _currentY = 456; }
			break;
		}
	}
	return _posType;
}

