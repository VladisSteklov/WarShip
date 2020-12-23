#pragma once
#include <random>
#include "Player.h"

class Computer : public Player {
public:
	Computer();
	std::pair <int, int>  make_move();
	Ship* getComputerShips();
private:
	Ship _computer_ships[10];
	std::default_random_engine* _random_engine;
	std::uniform_int_distribution<int>* _distribution_position_type;
	std::uniform_int_distribution <int>* _distribution_cordinatess;
	static sf::Vector2f _reverse_back_computer(std::pair <int, int>);
};


