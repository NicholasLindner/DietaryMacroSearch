#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

struct Text {
	Text() {}

	sf::Text setText(sf::Font& font, sf::String message, int size, sf::Color color, sf::Vector2f position) {
		sf::Text text;
		text.setFont(font);
		text.setString(message);
		text.setCharacterSize(size);
		text.setFillColor(color);
		sf::FloatRect rect = text.getLocalBounds();
		text.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		text.setPosition(position);
		return text;
	}
};