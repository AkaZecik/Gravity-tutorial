#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class Player {
public:
	Player(sf::Vector2f size) {
		player.setSize(size);
		player.setFillColor(sf::Color::Green);
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(player);
	}

	void move(sf::Vector2f distance) {
		player.move(distance);
	}

	void setPos(sf::Vector2f newPos) {
		player.setPosition(newPos);
	}
private:
	sf::RectangleShape player;
};