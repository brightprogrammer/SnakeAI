#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include <vector>

#include "common.hpp"
#include "config.hpp"
#include "snake.hpp"
#include "food.hpp"

static inline sf::Color screenClearColor = sf::Color(22, 4, 33);

void displayScore(size_t score, sf::RenderWindow& window){
	// font
	static sf::Font font;
	font.loadFromFile("../res/FATPIXEL.TTF");

	static sf::Text scoreText;

	// number of characters in
	static uint32_t lastStringSize = 0;
	std::string scoreString = std::to_string(score);
	scoreText.setFont(font);
	scoreText.setString(scoreString);
	scoreText.setFillColor(sf::Color(55, 29, 99, 100));
	scoreText.setCharacterSize(200);
	if(lastStringSize != scoreString.size()){
          // cache
		lastStringSize = scoreString.size();

		// change position
		scoreText.setPosition((windowWidth / 2.0) - ((scoreText.getLocalBounds().width /**lastStringSize*/) / 2.0),
							  (windowHeight / 2.0) - ((scoreText.getLocalBounds().height /**lastStringSize*/) / 2.0));
	}

	window.draw(scoreText);
}

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
		window.clear(screenClearColor);

		// display score
		displayScore(snake.getScore(), window);

		// draw snake and food
		food.drawSelf(window);
		snake.drawSelf(window);

		// show rendered things
		window.display();
	}

	return EXIT_SUCCESS;
}
