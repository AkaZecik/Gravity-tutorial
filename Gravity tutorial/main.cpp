#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Coin.h"
#include <sstream>

int main()
{
	sf::RenderWindow window;
	
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(900, 900), "SFML Gravity", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	// Player object:
	Player player({ 40, 70 });
	player.setPos({ 50, 700 });

	// Coin objects:
	std::vector<Coin*> coinVec;
	Coin coin1({ 20, 20 });
	Coin coin2({ 20, 20 });

	coin1.setPos({ 50, 600 });
	coin2.setPos({ 100, 600 });

	coinVec.push_back(&coin1);
	coinVec.push_back(&coin2);

	// Score objects:
	int score = 0;

	sf::Font arial;
	arial.loadFromFile("arial.ttf");

	std::ostringstream ssScore;
	ssScore << "Score: " << score;

	sf::Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setFont(arial);
	lblScore.setPosition({ 10, 10 });
	lblScore.setString(ssScore.str());

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

		// Coin logic:
		for (size_t i = 0; i < coinVec.size(); i++) {
			if (player.isColidingWithCoin(coinVec[i])) {
				coinVec[i]->setPos({ 42222, 523424 });
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
		}

		window.clear();
		window.draw(lblScore);
		coin1.drawTo(window);
		coin2.drawTo(window);
		player.drawTo(window);
		window.display();
	}

	return 0;
}