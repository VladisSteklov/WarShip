#pragma once
#include <SFML\Graphics.hpp>

class Map {
public:
	sf::Texture& get_fonTexture();
	sf::Texture& get_fieldTexture();
	sf::Texture& get_shipTexture();
	sf::Font& get_font();
	Map();
private:
	sf::Texture _fieldTexture;
	sf::Texture _shipTexture;
	sf::Texture _fonTexture;
	sf::Font _font;
};

sf::Sprite get_sprite(const sf::Texture&,const float&,const float&,const float&,const float&,const float&,const float&);
sf::Text get_text(const sf::Font&,const std::string&,const int&,const sf::Color&,const float&,const float&);
