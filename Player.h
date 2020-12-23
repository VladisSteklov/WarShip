#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <algorithm>
#include "Ship.h"

class Player {
public:
	enum MOVE_TYPE
	{
		GET,
		KILL,
		MISS
	};

	Player();
	void put_ship(const std::pair <int, int>&,const Ship::SHIP_TYPE&,const Ship::POSITION_TYPE&);
	bool check_ship(const std::pair <int,int>&, const Ship::SHIP_TYPE&, const Ship::POSITION_TYPE&);
	static std::pair <int, int> reverse(const sf::Vector2f&);
	static std::pair <int, int> reverseMapRight(const sf::Vector2f&);
	static sf::Vector2f reverse_back(const std::pair <int, int>&);
	MOVE_TYPE check_move(const std::pair <int,int>&);
	bool check_end_game();
	bool checkSameMove(const std::pair <int, int>&);

protected:
	int position_ships[10][10];
	std::vector <std::pair <int, int>> pushed_coordinates;
};

