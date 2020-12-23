#include "Menu.h"

Menu::Menu()
{
	_window.create(sf::VideoMode(1024, 819), "War of the ships", sf::Style::Titlebar | sf::Style::Close);

	_current_chose = ChosePlay::PLAY;

	// set fon-menu game
	sf::Texture fon;
	fon.loadFromFile("sourse/fon_menu.jpg");
	sf::Sprite sprite_fon = get_sprite(fon, 0, 0, 1024, 819, 0, 0);

	// set music-menu game
	sf::Music music_war_menu;
	music_war_menu.openFromFile("sourse/music_war_menu.ogg");
	music_war_menu.play();
	music_war_menu.setLoop(true);

	// set font-menu game
	sf::Font font;
	font.loadFromFile("sourse/CyrilicOld.ttf");

	// set text-menu
	sf::Text text_play = get_text(font, "Играть", 60, sf::Color::White, 440, 270);
	sf::Text text_exit = get_text(font, "Выход", 60, sf::Color::White, 440, 360);
	sf::Text text_back = get_text(font, "V1 VVS", 20, sf::Color::Black, 490, 780);

	// Событие нажатие клавиши обрабатывается один раз
	_window.setKeyRepeatEnabled(false);

	while (_window.isOpen())
	{
		while (_window.pollEvent(_event))
		{
			if (_event.type == sf::Event::EventType::Closed) 
				_window.close(); 

			if (_event.type == sf::Event::KeyPressed)
			{
				if (_event.key.code == sf::Keyboard::Down || _event.key.code == sf::Keyboard::Up)
				{
					if (_current_chose == ChosePlay::PLAY)  
						_current_chose = ChosePlay::EXIT;
					else 
						_current_chose = ChosePlay::PLAY;
				}
				if (_event.key.code == sf::Keyboard::Enter)
				{
					if (_current_chose == ChosePlay::EXIT) 
						_window.close();
					else
					{
						_window.close();
						music_war_menu.stop();

						// start the game
						Game game;
					}
				}
			}
		}
		
		if (sf::IntRect(400, 270, 250, 100).contains(sf::Mouse::getPosition(_window)))
		{
			_current_chose = ChosePlay::PLAY;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				_window.close();
				music_war_menu.stop();
				Game game;
			}

		}
		if (sf::IntRect(400, 360, 250, 100).contains(sf::Mouse::getPosition(_window)))
		{
			_current_chose = ChosePlay::EXIT;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				_window.close();
			}
		}

		switch (_current_chose)
		{
			case Menu::PLAY:
			{
				text_play.setFillColor(sf::Color::Red);
				text_exit.setFillColor(sf::Color::White);
				break;
			}
			case Menu::EXIT:
			{
				text_play.setFillColor(sf::Color::White);
				text_exit.setFillColor(sf::Color::Red);
				break;
			}
		}

		_window.clear(sf::Color::White);
		_window.draw(sprite_fon);

		_window.draw(text_play);
		_window.draw(text_exit);
		_window.draw(text_back);
		_window.display();

	}
}