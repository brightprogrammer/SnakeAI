#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include <vector>

#include "common.hpp"
#include "config.hpp"
#include "snake.hpp"
#include "food.hpp"

int main(){
	// where our rendered stuffs will appear
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle);

	// enable vsync
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(15);

	// create food
	Food food;

	// create snake
	Snake snake(food);

	// keep track of score
	size_t score = 0;

	// font
	sf::Font font;
	font.loadFromFile("../res/FATPIXEL.TTF");

	// score text to display score
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("0");
	scoreText.setFillColor(sf::Color(0, 0, 0xff, 0x80));
	scoreText.setCharacterSize(200);
	scoreText.setPosition(windowWidth / 2.0 - scoreText.getLocalBounds().width / 2.0,
						  windowHeight / 2.0 - scoreText.getLocalBounds().height / 2.0);

	// main game loop
	while (window.isOpen()) {
		// check for events
		sf::Event event;
		while (window.pollEvent(event)) {
			// if the window is being closed!
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// handle keyboard events
			if (event.type == sf::Event::KeyPressed) { 
		   		// update snake's position and stuffs
				snake.handleEvent(event);
            }
		}

		// clear color
		window.clear(sf::Color::Black);

		// draw score text
		scoreText.setString(std::to_string(snake.getScore()));
		window.draw(scoreText);

		// draw snake and food
		food.drawSelf(window);
		snake.drawSelf(window);

		// show rendered things
		window.display();
	}

	return EXIT_SUCCESS;
}
