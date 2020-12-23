#include "Game.h"

Game::Game() {
	// Load map to window-game
	Map map;

	_window.create(sf::VideoMode(1440, 900), "War of the ships", sf::Style::Titlebar | sf::Style::Close);

	_fon_sprite = get_sprite(map.get_fonTexture(), 0, 0, 1200, 790, 0, 0);
	_map_left_sprite = get_sprite(map.get_fieldTexture(), 0, 0, 450, 420, 150, 150);
	_map_right_sprite = get_sprite(map.get_fieldTexture(), 0, 0, 422, 420, 868, 150);

	_ship_texture = map.get_shipTexture();
	_font = map.get_font();

	// Set text to window-game
	_top_text = get_text(_font,"Добро пожаловать в игру Морской бой", 50, sf::Color(73, 2, 0), 320, 25);
	_bottom_text = get_text(_font, "Управление игрой\n - Для перемещения объектов используйте клавишы влево,\n вправо, вверх, вниз   \nДля фиксирования кораблей и выбора позиции\n нажмите Enter\n - Чтобы перевернуть корабль нажмите на клавишу R", 30, sf::Color(244, 249, 150), 660, 650);
	_left_text = get_text(_font,"Расставьте корабли", 30, sf::Color::Red, 220, 110);
	_right_text = get_text(_font,"Компьютер готов", 30, sf::Color::Red, 970, 110);

	// Render sprites of ships and music in another thread
	std::thread thrd_sprites(&Game::_render_ships_and_fields, this);
	thrd_sprites.detach();
	std::thread thrd_music(&Game::_render_music, this);
	thrd_music.detach();

	_stateGame = GameState::DISPOSAL;
	_counts_showedShips = 0; // Начальное число отображаемых кораблей равно нулю
	
	_window.setKeyRepeatEnabled(false); // Событие нажатие клавиши обрабатывается один раз

	// Game-Loop
	while (_window.isOpen()) {
		
		while (_window.pollEvent(_event)) {
			_event_handler();
		}

		// Clear the window
		_window.clear(sf::Color::White);

		// Show map sprites
		_window.draw(_fon_sprite);
		_window.draw(_map_left_sprite);
		_window.draw(_map_right_sprite);

		// Show text
		_window.draw(_top_text);
		_window.draw(_bottom_text);


		for (size_t i = 0; i <= _counts_showedShips; ++i) {
			auto curPos = ships[i].get_current_position();
			_ships_SpritesToShow[i]->setPosition(curPos.x, curPos.y);
			_window.draw(*_ships_SpritesToShow[i]);
		}

		// Game state: Diposal
		if (_stateGame == GameState::DISPOSAL) {
			_window.draw(_left_text);
			_window.draw(_right_text);
		}

		// Game state: Play or End
		if (_stateGame == GameState::PLAY || _stateGame == GameState::END) {
			// Получить позицию поля выбора на карте и отобразить ее
			auto curPos = _positionToCurField.get_current_position();
			_curPosition_sprite->setPosition(curPos.x, curPos.y);

			for (auto iter = _attacking_filedSprites.begin(); iter != _attacking_filedSprites.end(); ++iter) {
				_window.draw(*iter);
			}

			if (_computer.check_end_game() || _player.check_end_game()) {
				// Конец игры = Вывод всех кораблей
				_stateGame = GameState::END;
				sf::Text end_text;
				if (_computer.check_end_game()) {
					end_text = get_text(_font, "Вы победили! Поздравляем!\nДля выхода нажмите клавишу ESC", 28, sf::Color::Red, 320, 80);
				}
				else {
					end_text = get_text(_font, "Компьютер победил!\n Для выхода нажмите клавишу ESC", 28, sf::Color::Red, 350, 80);
				}
				_window.draw(end_text);

				for (size_t i = 0; i < 10; ++i) {
					// Вывод всех уничтоженных кораблей в случае, если игра закончена
					_window.draw(_shipsKilled_SpritesToShow[i]);
				}

			}

			for (auto iter_dager = _crest_Sprites.begin(); iter_dager != _crest_Sprites.end(); ++iter_dager) {
				// Вывод красного креста напротив уничтоженных кораблей
				sf::RectangleShape line(sf::Vector2f(42, 3));
				line.setFillColor(sf::Color::Red);
				line.rotate(45);
				line.setPosition(iter_dager->first + 2, iter_dager->second - 2);
				_window.draw(line);
				++iter_dager;
				line.rotate(90);
				line.setPosition((iter_dager)->first , (iter_dager)->second);
				_window.draw(line);
			}

			if (_stateGame == GameState::PLAY) {
				_window.draw(_right_text);
				_window.draw(*_curPosition_sprite);
			}
	
		}

		// Display window
		_window.display();

	}
}

// Game_hadler
void Game::_event_handler() {
	if (_event.type == sf::Event::EventType::Closed) // Закрытие окна
		_window.close();

	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape) { // Переход в меню
		_window.close();
		_music_war.stop();
		Menu menu;
	}

	if (_event.type == sf::Event::KeyPressed && _stateGame == GameState::DISPOSAL) { // Текущее состояние: Disposal - расстановка кораблей
		switch (_event.key.code) {
			case sf::Keyboard::Right: {
				_sound_tickMove.play();
				ships[_counts_showedShips].move(Ship::DIRECTION::RIGHT);
				break;
			}
			case sf::Keyboard::Left: {
				_sound_tickMove.play();
				ships[_counts_showedShips].move(Ship::DIRECTION::LEFT);
				break;
			}
			case sf::Keyboard::Up: {
				_sound_tickMove.play();
				ships[_counts_showedShips].move(Ship::DIRECTION::UP);
				break;
			}
			case sf::Keyboard::Down: {
				_sound_tickMove.play();
				ships[_counts_showedShips].move(Ship::DIRECTION::DOWN);
				break;
			}
			case sf::Keyboard::Enter: { // Install ship
				// Get info about ship
				auto cur_pos = ships[_counts_showedShips].get_current_position();
				Ship::SHIP_TYPE ship_type = ships[_counts_showedShips].get_ship_type();
				Ship::POSITION_TYPE position_type = ships[_counts_showedShips].get_position_type();

				if (_counts_showedShips <= 10 && _player.check_ship(Player::reverse(cur_pos), ship_type, position_type)) { 
					// Install ship
					_sound_installShip->play();
					++_counts_showedShips; 
					_player.put_ship(Player::reverse(cur_pos), ship_type, position_type);
				}

				if (_counts_showedShips == 10) {
					// All ships are installed
					_stateGame = GameState::PLAY;
					// 11-ый корабль не ставится, по этому необходимо уменьшить индекс последнего элемента массива ships
					--_counts_showedShips;

					_right_text = get_text(_font, "Ваш ход!", 32, sf::Color::Red, 1020, 110);
					std::thread render_ship_end_thread(&Game::_render_ship_end_game, this);
					render_ship_end_thread.detach();

					// Удалить буфер и музыку установки кораблей
					delete _buffeSound_installShip;
					delete _sound_installShip;
				}
				break;
			}
			case sf::Keyboard::R:
			{
				// Перевернуть корабль
				_sound_tickMove.play();
				Ship::POSITION_TYPE new_type = ships[_counts_showedShips].reverse();
				Ship::SHIP_TYPE type = ships[_counts_showedShips].get_ship_type();
				switch (type)
				{
					case Ship::QUAD:
					{
						if (new_type == Ship::POSITION_TYPE::VERTICAL)
							_ships_SpritesToShow[_counts_showedShips] = _renderShip_Sprites[1];
						else
							_ships_SpritesToShow[_counts_showedShips] = _renderShip_Sprites[0];
						break;
					}
					case Ship::TRIPLE:
					{
						if (new_type == Ship::POSITION_TYPE::VERTICAL)
							_ships_SpritesToShow[_counts_showedShips] = _renderShip_Sprites[3];
						else
							_ships_SpritesToShow[_counts_showedShips] = _renderShip_Sprites[2];
						break;
					}
					case Ship::DOUBLE:
					{
						if (new_type == Ship::POSITION_TYPE::VERTICAL)
							_ships_SpritesToShow[_counts_showedShips] = _renderShip_Sprites[5];
						else
							_ships_SpritesToShow[_counts_showedShips] = _renderShip_Sprites[4];
						break;
					}
					case Ship::SINGLE:
					{
						if (new_type == Ship::POSITION_TYPE::VERTICAL)
							_ships_SpritesToShow[_counts_showedShips] = _renderShip_Sprites[7];
						else
							_ships_SpritesToShow[_counts_showedShips] = _renderShip_Sprites[6];
						break;
					}
				}
				break;
			}
		}
		return;
	}

	if (_event.type == sf::Event::KeyPressed && _stateGame == GameState::PLAY) { // Текущее состояние: Play - игра
		switch (_event.key.code)
		{
			case sf::Keyboard::Right:
			{
				// Передвинуть позицию
				_sound_tickMove.play();
				_positionToCurField.move(Position::DIRECTION::RIGHT);
				break;
			}
			case sf::Keyboard::Left:
			{
				// Передвинуть позицию
				_sound_tickMove.play();
				_positionToCurField.move(Position::DIRECTION::LEFT);
				break;
			}
			case sf::Keyboard::Up:
			{
				// Передвинуть позицию
				_sound_tickMove.play();
				_positionToCurField.move(Position::DIRECTION::UP);
				break;
			}
			case sf::Keyboard::Down:
			{
				// Передвинуть позицию
				_sound_tickMove.play();
				_positionToCurField.move(Position::DIRECTION::DOWN);
				break;
			}

			case sf::Keyboard::Enter:
			{
				// Ход пользователя
				auto curPos = _positionToCurField.get_current_position();
				auto pair = Player::reverseMapRight(curPos);
				_sound_shot.play();
				if (_player.checkSameMove(pair)) {// Если такой ход был осуществлен пользовтелем ранее
					_right_text = get_text(_font, "Такой ход уже был!", 32, sf::Color::Red, 948, 110);
				}
				else {
					Player::MOVE_TYPE type = _computer.check_move(pair);
					if (type == Player::MOVE_TYPE::KILL || type == Player::MOVE_TYPE::GET)
					{
						_draw_lines(curPos);
						if (type == Player::MOVE_TYPE::KILL) {
							_right_text = get_text(_font, "Корабль уничтожен!", 32, sf::Color::Red,	948, 110);
						}
						else {
							_right_text = get_text(_font, "Попадание по кораблю!", 32, sf::Color::Red,		930, 110);
						}
					}
					else { // Промах
						_right_text = get_text(_font, "Промах!", 32, sf::Color::Red, 1034, 110);
						sf::Sprite& temp_sprite = _renderField_Sprites[1];
						temp_sprite.setPosition(curPos.x, curPos.y);
						_attacking_filedSprites.push_back(temp_sprite);
					}
				}

				// Ход компьютера
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				// Сделать ход компьютером
				pair = _computer.make_move();
				// Издать звук выстрела
				_sound_shot.play();
				// Проверка выстрела пользователем
				_player.check_move(pair);
				curPos = Player::reverse_back(pair);
				_draw_lines(curPos);
			
				break;
			}
		}
		return;
	}
	if (_event.type == sf::Event::KeyPressed && _stateGame == GameState::END)
	{
		if (_event.key.code == sf::Keyboard::Escape)
		{
			_window.close();
		}
	}
}

void Game::_draw_lines(sf::Vector2f coordinates) {
	_crest_Sprites.push_back(std::pair <float, float>(coordinates.x, coordinates.y));
	_crest_Sprites.push_back(std::pair <float, float>(coordinates.x + 32, coordinates.y));
}

void Game::_render_music() {

	_buffeSound_installShip = new sf::SoundBuffer;
	_sound_installShip = new sf::Sound;

	// Set music for tick when ship is installing
	_buffeSound_installShip->loadFromFile("sourse/instal.ogg");
	_sound_installShip->setBuffer(*_buffeSound_installShip);
	_sound_installShip->setVolume(30);

	// Set music for tick when ship is going on map
	_bufferSound_tickMove.loadFromFile("sourse/tick.ogg");
	_sound_tickMove.setBuffer(_bufferSound_tickMove);
	_sound_tickMove.setVolume(30);

	// Set music for gun-shots
	_bufferSound_shot.loadFromFile("sourse/shot.ogg");
	_sound_shot.setBuffer(_bufferSound_shot);
	_sound_shot.setVolume(30);

	// Set music for game
	_music_war.openFromFile("sourse/music_war.ogg");
	_music_war.play();
	_music_war.setLoop(true);
}



void Game::_render_ships_and_fields() {

	// Make ships sprites
	_renderShip_Sprites[0] = std::make_shared<sf::Sprite>(get_sprite(_ship_texture, 0, 0, 128, 30, 200, 200));
	_renderShip_Sprites[1] = std::make_shared<sf::Sprite>(get_sprite(_ship_texture, 185, 0, 30, 128, 200,200));
	_renderShip_Sprites[2] = std::make_shared<sf::Sprite>(get_sprite(_ship_texture, 0, 33, 96, 30, 200, 200));
	_renderShip_Sprites[3] = std::make_shared<sf::Sprite>(get_sprite(_ship_texture, 217, 0, 30, 96, 200, 200));
	_renderShip_Sprites[4] = std::make_shared<sf::Sprite>(get_sprite(_ship_texture, 0, 65, 64, 30, 200, 200));
	_renderShip_Sprites[5] = std::make_shared<sf::Sprite>(get_sprite(_ship_texture, 248, 0, 30, 64, 200, 200));
	_renderShip_Sprites[6] = std::make_shared<sf::Sprite>(get_sprite(_ship_texture, 0, 97, 30, 30, 200, 200));
	_renderShip_Sprites[7] = std::make_shared<sf::Sprite>(get_sprite(_ship_texture, 280, 0, 30, 30, 200, 200));

	// Инициализация вектора спрайтов для установки кораблей
	_ships_SpritesToShow.resize(10);
	
	_ships_SpritesToShow[0] = _renderShip_Sprites[0];
	_ships_SpritesToShow[1] = _renderShip_Sprites[2];
	_ships_SpritesToShow[2] = _renderShip_Sprites[2];
	_ships_SpritesToShow[3] = _renderShip_Sprites[4];
	_ships_SpritesToShow[4] = _renderShip_Sprites[4];
	_ships_SpritesToShow[5] = _renderShip_Sprites[4];
	_ships_SpritesToShow[6] = _renderShip_Sprites[6];
	_ships_SpritesToShow[7] = _renderShip_Sprites[6];
	_ships_SpritesToShow[8] = _renderShip_Sprites[6];
	_ships_SpritesToShow[9] = _renderShip_Sprites[6];

	// Загрузка текстуры полей выстрела и промаха
	_field_texture.loadFromFile("sourse/field.png");
	// Формирование спрайтов
	_renderField_Sprites[0] = get_sprite(_field_texture, 0, 0, 31, 32, 918, 200);  // Прицел
	_renderField_Sprites[1] = get_sprite(_field_texture, 0, 36, 31, 32, 900, 565); // Промах

	// Установить спрайт текущего поля прицелом
	_curPosition_sprite = &_renderField_Sprites[0];
	return;
}

void Game::_render_ship_end_game() {
	// Cформировать вектор ссылок на спрайты кораблей от компьютера
	_shipsKilled_SpritesToShow.resize(10);
	auto ships = _computer.getComputerShips(); // Получить массив кораблей от компьютера
	for (size_t i = 0; i < 10; ++i) {
		// Получить информацию о корабле
		Ship::SHIP_TYPE type = ships[i].get_ship_type();
		Ship::POSITION_TYPE pos_type = ships[i].get_position_type();
		sf::Vector2f cordinates = ships[i].get_current_position();
		switch (type) {
			case Ship::SHIP_TYPE::QUAD: {
				if (pos_type == Ship::POSITION_TYPE::GORIZONTAL) {
					_shipsKilled_SpritesToShow[i] = *_renderShip_Sprites[0];
				}
				else {
					_shipsKilled_SpritesToShow[i] = *_renderShip_Sprites[1];
				}
				break;
			}
			case Ship::SHIP_TYPE::TRIPLE: {
				if (pos_type == Ship::POSITION_TYPE::GORIZONTAL) {
					_shipsKilled_SpritesToShow[i] = *_renderShip_Sprites[2];
				}
				else {
					_shipsKilled_SpritesToShow[i] = *_renderShip_Sprites[3];
				}
				break;
			}
			case Ship::SHIP_TYPE::DOUBLE:
			{
				if (pos_type == Ship::POSITION_TYPE::GORIZONTAL) {
					_shipsKilled_SpritesToShow[i] = *_renderShip_Sprites[4];
				}
				else {
					_shipsKilled_SpritesToShow[i] = *_renderShip_Sprites[5];
				}
				break;
			}
			case Ship::SHIP_TYPE::SINGLE: {
				if (pos_type == Ship::POSITION_TYPE::GORIZONTAL) {
					_shipsKilled_SpritesToShow[i] = *_renderShip_Sprites[6];
				}
				else {
					_shipsKilled_SpritesToShow[i] = *_renderShip_Sprites[7];
				}
				break;
			}
		}
		_shipsKilled_SpritesToShow[i].setPosition(cordinates);
	}
}