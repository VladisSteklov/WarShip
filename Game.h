#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <thread>
#include "Map.h"
#include "Ship.h"
#include "Player.h"
#include "Computer.h"
#include "Position.h"
#include "Menu.h"

class Game
{
public:
	enum GameState
	{
		DISPOSAL,
		PLAY,
		END
	};

	Game();

private:
	// enum of current state game
	GameState _stateGame;

	// Player and Computer
	Player _player;
	Computer _computer;

	// SoundBuffers and Sounds
	sf::SoundBuffer _bufferSound_tickMove;
	sf::Sound _sound_tickMove;

	sf::SoundBuffer* _buffeSound_installShip;
	sf::Sound* _sound_installShip;

	sf::SoundBuffer _bufferSound_shot;
	sf::Sound _sound_shot;

	// Musics
	sf::Music _music_war;

	// Windows and events
	sf::RenderWindow _window;
	sf::Event _event;

	// ������� ���� ��������
	sf::Texture _ship_texture;

	// ������� ���� ��� ������� ��� �������
	sf::Texture _field_texture;

	// Spirtes of Ships

	// ������ �������� ���� ����� ��������
	std::shared_ptr<sf::Sprite> _renderShip_Sprites[8];
	// ������ �������� �������� ��� ������ ����� ��������� ����
	std::vector<std::shared_ptr<sf::Sprite>> _ships_SpritesToShow;
	// ������ �������� �������� ��� ������ �� ����� ����
	std::vector<sf::Sprite> _shipsKilled_SpritesToShow;

	// ������ �������� ��� ����� (������ ��� ������)
	sf::Sprite _renderField_Sprites[2];
	// ������ �������� ����
	//std::shared_ptr<sf::Sprite> _curPosition_sprite;
	sf::Sprite* _curPosition_sprite;

	// ������ �������� ����������� �����
	std::vector <sf::Sprite> _attacking_filedSprites;
	// ������ ��������� ������� �������
	std::vector <std::pair <float, float >> _crest_Sprites;

	// Sprites of map
	sf::Sprite _fon_sprite;
	sf::Sprite _map_left_sprite;
	sf::Sprite _map_right_sprite;

	// Fonts
	sf::Font _font;

	// Texts
	sf::Text _top_text;
	sf::Text _bottom_text;
	sf::Text _left_text;
	sf::Text _right_text;

	// ������ �������� ������������
	Ship ships[10];

	// ������ ������� (������)
	Position _positionToCurField;

	// ����� �������� ��������, ������� ������������ � ������ ������ �������
	int _counts_showedShips;

	// ���������� �������
	void _event_handler();

	// Render methods
	void _render_ships_and_fields();
	void _render_music();
	void _render_ship_end_game();

	// ����� ��������� �������� ������
	void _draw_lines(sf::Vector2f);
};

