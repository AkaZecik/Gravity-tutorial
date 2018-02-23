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

	Player player({ 40, 40 });
	player.setPos({ 50, 700 });


	// main loop:
	while (window.isOpen())
	{
		sf::Event event;

		// event loop:
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			}
		}

		window.clear();
		player.drawTo(window);
		window.display();
	}

	return 0;
}