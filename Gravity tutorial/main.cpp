#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
	sf::RenderWindow window;
	
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(900, 900), "SFML Gravity", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	Player player({ 40, 70 });
	player.setPos({ 50, 700 });

	// Gravity variables:
	const int groundHeight = 700;
	const float gravitySpeed = static_cast<float>(0.3);
	bool isJumping = false;

	// main loop:
	while (window.isOpen())
	{
		sf::Event event;

		const float moveSpeed = static_cast<float>(0.2);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.move({ 0, -moveSpeed });
			isJumping = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.move({ moveSpeed, 0 });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.move({ -moveSpeed, 0 });
		}

		// event loop:
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case sf::Event::Closed: {
					window.close();
				} break;
				case sf::Event::KeyReleased: {
					if (event.key.code == sf::Keyboard::Up) {
						isJumping = false;
					}
				} break;
			}
		}

		//Gravity logic:
		if (player.getY() < groundHeight && isJumping == false) {
			player.move({ 0, gravitySpeed });
		}

		window.clear();
		player.drawTo(window);
		window.display();
	}

	return 0;
}