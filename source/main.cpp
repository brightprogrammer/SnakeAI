#include <string>
#include <vector>

#include "common.hpp"
#include "snake.hpp"

int main(){
	// where our rendered stuffs will appear
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle);

	// enable vsync
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(15);

	// create player
	Snake player;

	// main game loop
	while (window.isOpen()) {
		// check for events
		sf::Event event;
		while (window.pollEvent(event)) {
			// if the window is being closed!
			if(event.type == sf::Event::Closed){
				window.close();
			}

			// handle keyboard events
			if(event.type == sf::Event::KeyPressed){
				// update snake's position and stuffs
				player.handleEvent(event);
			}
		}

		// clear color
		window.clear(sf::Color::Black);

		// draw snake head
		player.drawSelf(window);

		// show rendered things
		window.display();
	}

	return EXIT_SUCCESS;
}
