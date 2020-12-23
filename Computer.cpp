#include "Computer.h"

Computer::Computer() {
	
	_random_engine = new std::default_random_engine(time(static_cast<uint32_t>(0)));
	_distribution_position_type = new std::uniform_int_distribution <int>(0, 1);
	_distribution_cordinatess = new std::uniform_int_distribution <int>(0, 9);

	std::pair <int, int> cordinates;
	int type_position;
	Ship::SHIP_TYPE S_TYPE;

	// Generate Ship params
	int i = 0;
	while (i < 10) {
		type_position = (*_distribution_position_type)(*_random_engine);
		int type_ship = ships_constArr[i];

		bool flag = false;
		switch (type_ship) {
			case 4: {
				S_TYPE = Ship::SHIP_TYPE::QUAD;
				break;
			}
			case 3: {
				S_TYPE = Ship::SHIP_TYPE::TRIPLE;
				break;
			}
			case 2: {
				S_TYPE = Ship::SHIP_TYPE::DOUBLE;
				break;
			}
			case 1: {
				S_TYPE = Ship::SHIP_TYPE::SINGLE;
				break;
			}
		
		}
		do {
			cordinates.first = (*_distribution_cordinatess)(*_random_engine);
			cordinates.second = (*_distribution_cordinatess)(*_random_engine);
			switch (type_position) {
				case 0: { // Горизонтальная позиция
					if ((cordinates.second <= 6 && S_TYPE == Ship::SHIP_TYPE::QUAD) ||
						(cordinates.second <= 7 && S_TYPE == Ship::SHIP_TYPE::TRIPLE) ||
						(cordinates.second <= 8 && S_TYPE == Ship::SHIP_TYPE::DOUBLE) ||
						(cordinates.second <=9 && S_TYPE == Ship::SHIP_TYPE::SINGLE))
					{
						flag = true;
						if (check_ship(cordinates, S_TYPE, Ship::POSITION_TYPE::GORIZONTAL))
						{
							put_ship(cordinates, S_TYPE, Ship::POSITION_TYPE::GORIZONTAL);
							_computer_ships[i].setPositionType(Ship::POSITION_TYPE::GORIZONTAL);
							sf::Vector2f vec = this->_reverse_back_computer(cordinates);
							_computer_ships[i].setPosition(vec.x,vec.y);
							i++;
						}
					}
					break;
				}
				case 1: { // Вертикальная позиция		
					if ((cordinates.first <= 6 && S_TYPE == Ship::SHIP_TYPE::QUAD) ||
						(cordinates.first <= 7 && S_TYPE == Ship::SHIP_TYPE::TRIPLE) ||
						(cordinates.first <= 8 && S_TYPE == Ship::SHIP_TYPE::DOUBLE)||
						cordinates.first <= 9 && S_TYPE == Ship::SHIP_TYPE::SINGLE)
					{
						flag = true;
						if (check_ship(cordinates, S_TYPE, Ship::POSITION_TYPE::VERTICAL))
						{
							put_ship(cordinates, S_TYPE, Ship::POSITION_TYPE::VERTICAL);
							_computer_ships[i].setPositionType(Ship::POSITION_TYPE::VERTICAL);
							sf::Vector2f vec = this->_reverse_back_computer(cordinates);
							_computer_ships[i].setPosition(vec.x, vec.y);
							i++;
						}
					}
					break;
				}
			}
		} while (flag == false);
		
	}
	delete _distribution_position_type;
}

Ship* Computer::getComputerShips() {
	return _computer_ships;
}

sf::Vector2f Computer::_reverse_back_computer(std::pair <int, int> pair) {
	return sf::Vector2f(pair.second * 32 + 918, pair.first * 32 + 200);
}

std::pair <int, int > Computer::make_move() {
	std::pair <int, int> coordinates;
	do {
		coordinates.first = (*_distribution_cordinatess)(*_random_engine);
		coordinates.second = (*_distribution_cordinatess)(*_random_engine);
	} while (checkSameMove(coordinates));

	return coordinates;
}