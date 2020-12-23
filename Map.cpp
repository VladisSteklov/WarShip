#include "Map.h"


Map::Map() {
	_fieldTexture.loadFromFile("sourse/map.png");
	 _shipTexture.loadFromFile("sourse/ships.png");
	 _fonTexture.loadFromFile("sourse/fon_main.jpg");
	_font.loadFromFile("sourse/CyrilicOld.ttf");
}

sf::Texture& Map::get_fonTexture() {
	return _fonTexture;
}

sf::Texture& Map::get_fieldTexture() {
	return _fieldTexture;
}

sf::Texture& Map::get_shipTexture() {
	return _shipTexture;
}

sf::Font& Map::get_font() {
	return _font;
}

sf::Text get_text(const sf::Font &font,const std::string& str,const int& size,const sf::Color& color,
	const float& x,const float& y) {
	sf::Text text;
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setOutlineColor(sf::Color::Black);
	text.setFillColor(color);
	text.setPosition(x, y);
	text.setStyle(sf::Text::Bold);
	text.setStyle(sf::Text::Italic);
	return text;
}



sf::Sprite get_sprite(const sf::Texture &textur,const float &rect_x,const float &rect_y,const float &width,const float &height,
	const float &position_x,const float &position_y) {
	sf::Sprite spr;
	spr.setTexture(textur);
	spr.setTextureRect(sf::IntRect(rect_x, rect_y, width, height));
	spr.setPosition(position_x, position_y);
	return spr;
}