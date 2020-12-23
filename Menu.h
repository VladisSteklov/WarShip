#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Game.h"

class Menu
{
public:
	Menu();
	enum ChosePlay
	{
		PLAY,
		EXIT
	};
private:
	sf::RenderWindow _window;
	sf::Event _event;
	ChosePlay _current_chose;
};

