#include "Player.h"



Player::Player() {
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			position_ships[i][j] = 0;
		}
	}
}

std::pair <int, int> Player::reverse(const sf::Vector2f& vec) {
	return std::pair <int, int>((vec.y - 200) / 32, (vec.x - 200) / 32);
}

std::pair <int, int> Player::reverseMapRight(const sf::Vector2f& vec) {
	return std::pair <int, int>((vec.y - 200) / 32, (vec.x - 918) / 32);
}

sf::Vector2f Player::reverse_back(const std::pair <int, int>& pair) {
	return sf::Vector2f(200 + 32 * pair.second, 200 + 32 * pair.first);
}



Player::MOVE_TYPE Player::check_move(const std::pair <int, int>& pair) {
	if (position_ships[pair.first][pair.second] == 0) 
		return MOVE_TYPE::MISS;
	else {
		auto type = position_ships[pair.first][pair.second];
		position_ships[pair.first][pair.second] = 5; // Уничтожаем корабль
		if (type == 1)	
			return MOVE_TYPE::KILL;
		if (pair.first - 1 >= 0) {
			if (position_ships[pair.first - 1][pair.second] == type) 
				return MOVE_TYPE::GET;
			if (position_ships[pair.first - 1][pair.second] == 5) { 
				if (type == 2) 
					return MOVE_TYPE::KILL;
				else {
					if (pair.first -2 >= 0) {
						if (position_ships[pair.first - 2][pair.second] == 5) {
							if (type == 3) 
								return MOVE_TYPE::KILL;
							else {
								if (pair.first - 3 >= 0) {
									if (position_ships[pair.first - 3][pair.second] == 5)
										if (type == 4)
											return MOVE_TYPE::KILL;
								}
							}
						}
					}

				}
				
			}
		}
		if (pair.first + 1 <= 9) {
			if (position_ships[pair.first + 1][pair.second] == type) { return MOVE_TYPE::GET; }
			if (position_ships[pair.first + 1][pair.second] == 5) 
			{  
				if (type == 2) { return MOVE_TYPE::KILL; }
				else
				{
					if (pair.first + 2 <= 9)
					{
						if (position_ships[pair.first + 2][pair.second] == 5)
						{
							if (type == 3) { return MOVE_TYPE::KILL; }
							else
							{
								if (pair.first + 3 <= 9)
								{
									if (position_ships[pair.first + 3][pair.second] == 5)
										if (type == 4) return MOVE_TYPE::KILL;
								}
							}
						}
					}
				}
			}
		}			
		if (pair.second - 1 >= 0) {
			if (position_ships[pair.first][pair.second - 1] == type) { return MOVE_TYPE::GET; }
			if (position_ships[pair.first][pair.second - 1] == 5) 
			{ 
				if (type == 2) { return MOVE_TYPE::KILL; }
				else
				{
					if (pair.second - 2 >= 0)
					{
						if (position_ships[pair.first][pair.second - 2] == 5)
						{
							if (type == 3) { return MOVE_TYPE::KILL; }
							else
							{
								if (pair.second - 3 >= 0)
								{
									if (position_ships[pair.first][pair.second - 3] == 5)
										if (type == 4)
											return MOVE_TYPE::KILL;
								}
							}
						}
					}
				}
			}
		}
		if (pair.second + 1 <= 9) {				
			if (position_ships[pair.first][pair.second + 1] == type) 
				return MOVE_TYPE::GET;
			if (position_ships[pair.first][pair.second + 1] == 5) {  
				if (type == 2) 
					return MOVE_TYPE::KILL;
				else {
					if (pair.second + 2 <= 9) {
						if (position_ships[pair.first][pair.second + 2] == 5) {
							if (type == 3) { return MOVE_TYPE::KILL; }
							else {
								if (pair.second + 3 <= 9) {
									if (position_ships[pair.first][pair.second + 3] == 5)
										if (type == 4) 
											return MOVE_TYPE::KILL;
								}
							}
						}
					}
				}
			}
		}
		if (type == 3) {
			if (pair.first - 1 >= 0 && pair.first + 1 <= 9) {
				if (position_ships[pair.first - 1][pair.second] == 5 &&
					position_ships[pair.first + 1][pair.second] == 5)
					return MOVE_TYPE::KILL;
			}
			if (pair.second - 1 >= 0 && pair.second + 1 <= 9) {
				if (position_ships[pair.first][pair.second - 1] == 5 &&
					position_ships[pair.first][pair.second + 1] == 5)
					return MOVE_TYPE::KILL;
			}
		}
		if (type == 4) {
			if (pair.first - 1 >= 0 && pair.first + 2 <= 9) {
				if (position_ships[pair.first - 1][pair.second] == 5 && position_ships[pair.first + 1][pair.second] == 5 && position_ships[pair.first + 2][pair.second] == 5)
					return MOVE_TYPE::KILL;
			}
			if (pair.first - 2 >= 0 && pair.first + 1 <= 9) {
				if (position_ships[pair.first + 1][pair.second] == 5 && position_ships[pair.first - 1][pair.second] == 5 && position_ships[pair.first - 2][pair.second] == 5)
					return MOVE_TYPE::KILL;
			}
			if (pair.second - 1 >= 0 && pair.second + 2 <= 9) {
				if (position_ships[pair.first][pair.second - 1] == 5 && position_ships[pair.first][pair.second + 1] == 5 && position_ships[pair.first][pair.second + 2] == 5)
					return MOVE_TYPE::KILL;
			}
			if (pair.second - 2 >= 0 && pair.second + 1 <= 9){
				if (position_ships[pair.first][pair.second - 1] == 5 && position_ships[pair.first][pair.second - 2] == 5 && position_ships[pair.first][pair.second + 1] == 5)
					return MOVE_TYPE::KILL;
			}
		}
	}

	return MOVE_TYPE::GET;
}

bool Player::checkSameMove(const std::pair <int ,int>& pair) {
	if (std::find(pushed_coordinates.begin(), pushed_coordinates.end(), pair) != pushed_coordinates.end())
		return true; // Такой ход уже был
	else
	{
		pushed_coordinates.push_back(pair);
		return false; // Такого хода не было
	}
}

bool Player::check_end_game() {
	bool flag = true;
	int i = 0, j;
	while (i < 10 && flag)
	{
		j = 0;
		while (j < 10 && flag)
		{
			if (position_ships[i][j] != 0 && position_ships[i][j] != 5)
			{
				flag = false;
			}
			j++;
		}
		i++;
	}
	return flag;
}

void Player:: put_ship(const std::pair <int, int>& cord,const Ship::SHIP_TYPE& S_TYPE,const Ship::POSITION_TYPE& P_TYPE) {
	auto x = cord.first; 
	auto y = cord.second;
	switch (S_TYPE)
	{
		case Ship::QUAD:{
			if (P_TYPE == Ship::POSITION_TYPE::GORIZONTAL)
				for (size_t i = 0; i < 4; i++)
					position_ships[x][y + i] = 4;
			else
				for (size_t i = 0; i < 4; i++)
					position_ships[x + i][y] = 4;
			break;
		}
		case Ship::TRIPLE: {
			if (P_TYPE == Ship::POSITION_TYPE::GORIZONTAL)
				for (size_t i = 0; i < 3; i++)
					position_ships[x][y + i] = 3;
			else
				for (size_t i = 0; i < 3; i++)
					position_ships[x + i][y] = 3;
			break;
		}
		case Ship::DOUBLE: {
			if (P_TYPE == Ship::POSITION_TYPE::GORIZONTAL)
				for (size_t i = 0; i < 2; i++)
					position_ships[x][y + i] = 2;
			else
				for (size_t i = 0; i < 2; i++)
					position_ships[x + i][y] = 2;
			break;
		}
		case Ship::SINGLE: {
			if (P_TYPE == Ship::POSITION_TYPE::GORIZONTAL)
				position_ships[x][y] = 1;
			else
				position_ships[x][y] = 1;
			break;
		}
	}
}

bool Player::check_ship(const std::pair <int,int>& cord,const Ship::SHIP_TYPE& S_TYPE,const Ship::POSITION_TYPE& P_TYPE) {
	int x = cord.first; int y = cord.second;

	switch (S_TYPE)
	{
		case Ship::QUAD:
		{
			if (P_TYPE == Ship::POSITION_TYPE::GORIZONTAL)
			{
				for (int i = -1; i < 5; i++)
				{
					if (y + i < 0) { i = 0; }
					if (y + i > 9) { break; }
					if (x - 1 < 0)
					{
						if (position_ships[x][y + i] != 0 || position_ships[x + 1][y + i] != 0)
							return false;
					}
					if (x + 1 > 9)
					{
						if (position_ships[x][y + i] != 0 || position_ships[x - 1][y + i] != 0)
							return false;
					}
					if (x >= 1 && x <= 8) 
					{
						if (position_ships[x - 1][y + i] != 0 || position_ships[x][y + i] != 0 ||
							position_ships[x + 1][y + i] != 0)
							return false;
					}
				}
			}
			else
			{
				for (int i = -1; i < 5; i++)
				{
					if (x + i < 0) { i = 0; }
					if (x + i > 9) { break; }

					if (y - 1 < 0)
					{
						if (position_ships[x + i][y] != 0 || position_ships[x + i][y + 1] != 0)
							return false;
					}
					if (y + 1 > 9)
					{
						if (position_ships[x + i][y] != 0 || position_ships[x + i][y - 1] != 0)
							return false;
					}
					if (y >= 1 && y <= 8)
					{
						if (position_ships[x + i][y - 1] != 0 || position_ships[x + i][y] != 0 ||
							position_ships[x + i][y + 1] != 0)
							return false;
					}
			
				}
			}
			break;
		}
		case Ship::TRIPLE:
		{
			if (P_TYPE == Ship::POSITION_TYPE::GORIZONTAL) 
			{
				for (int i = -1; i < 4; i++)
				{
					if (y + i < 0) { i = 0; }
					if (y + i > 9) { break; }

					if (x - 1 < 0)
					{
						if (position_ships[x][y + i] != 0 || position_ships[x + 1][y + i] != 0)
							return false;
					}
					if (x + 1 > 9)
					{
						if (position_ships[x][y + i] != 0 || position_ships[x - 1][y + i] != 0)
							return false;
					}
					if (x >= 1 && x <= 8)
					{
						if (position_ships[x - 1][y + i] != 0 || position_ships[x][y + i] != 0 ||
							position_ships[x + 1][y + i] != 0)
							return false;
					}
				}
			}
			else
			{
				for (int i = -1; i < 4; i++)
				{
					if (x + i < 0) { i = 0; }
					if (x + i > 9) { break; }

					if (y - 1 < 0)
					{
						if (position_ships[x + i][y] != 0 || position_ships[x + i][y + 1] != 0)
							return false;
					}
					if (y + 1 > 9)
					{
						if (position_ships[x + i][y] != 0 || position_ships[x + i][y - 1] != 0)
							return false;
					}
					if (y >= 1 && y <= 8)
					{
						if (position_ships[x + i][y - 1] != 0 || position_ships[x + i][y] != 0 ||
							position_ships[x + i][y + 1] != 0)
							return false;
					}
				}
			}
			break;
		}
		case Ship::DOUBLE:
		{
			if (P_TYPE == Ship::POSITION_TYPE::GORIZONTAL)
			{
				for (int i = -1; i < 3; i++)
				{
					if (y + i < 0) { i = 0; }
					if (y + i > 9) { break; }

					if (x - 1 < 0)
					{
						if (position_ships[x][y + i] != 0 || position_ships[x + 1][y + i] != 0)
							return false;
					}
					if (x + 1 > 9)
					{
						if (position_ships[x][y + i] != 0 || position_ships[x - 1][y + i] != 0)
							return false;
					}
					if (x >= 1 && x <= 8)
					{
						if (position_ships[x - 1][y + i] != 0 || position_ships[x][y + i] != 0 ||
							position_ships[x + 1][y + i] != 0)
							return false;
					}
				}
			}
			else 
			{
				for (int i = -1; i < 3; i++)
				{
					if (x + i < 0) { i = 0; }
					if (x + i > 9) { break; }

					if (y - 1 < 0)
					{
						if (position_ships[x + i][y] != 0 || position_ships[x + i][y + 1] != 0)
							return false;
					}
					if (y + 1 > 9)
					{
						if (position_ships[x + i][y] != 0 || position_ships[x + i][y - 1] != 0)
							return false;
					}
					if (y >= 1 && y <= 8)
					{
						if (position_ships[x + i][y - 1] != 0 || position_ships[x + i][y] != 0 ||
							position_ships[x + i][y + 1] != 0)
							return false;
					}
				}
			}
			break;
		}
		case Ship::SINGLE:
		{
			if (P_TYPE == Ship::POSITION_TYPE::GORIZONTAL)
			{
				for (int i = -1; i < 2; i++)
				{
					if (y + i < 0) { i = 0; }
					if (y + i > 9) { break; }

					if (x - 1 < 0)
					{
						if (position_ships[x][y + i] != 0 || position_ships[x + 1][y + i] != 0)
							return false;
					}
					if (x + 1 > 9)
					{
						if (position_ships[x][y + i] != 0 || position_ships[x - 1][y + i] != 0)
							return false;
					}
					if (x >= 1 && x <= 8)
					{
						if (position_ships[x - 1][y + i] != 0 || position_ships[x][y + i] != 0 ||
							position_ships[x + 1][y + i] != 0)
							return false;
					}
				}
			}
			else 
			{
				for (int i = -1; i < 2; i++)
				{
					if (x + i < 0) { i = 0; }
					if (x + i > 9) { break; }

					if (y - 1 < 0)
					{
						if (position_ships[x + i][y] != 0 || position_ships[x + i][y + 1] != 0)
							return false;
					}
					if (y + 1 > 9)
					{
						if (position_ships[x + i][y] != 0 || position_ships[x + i][y - 1] != 0)
							return false;
					}
					if (y >= 1 && y <= 8)
					{
						if (position_ships[x + i][y - 1] != 0 || position_ships[x + i][y] != 0 ||
							position_ships[x + i][y + 1] != 0)
							return false;
					}
				}
			}
			break;
		}
	}
	return true;
}