#include "food.hpp"

// food constructor
Food::Food() {
	foodImg.create(gridSize, gridSize, sf::Color::Green);
	foodTexture.loadFromImage(foodImg);
	food.setTexture(foodTexture);

	resetPosition();
}

// draw self to screen
void Food::drawSelf(sf::RenderWindow &window) { window.draw(food); }

// reset to random position
void Food::resetPosition() {
	// get a random position snapped to grid
	sf::Vector2f randPos;
	randPos.x = static_cast<size_t>(rand() % windowWidth);
	randPos.x -= static_cast<size_t>(randPos.x) % gridSize;
	randPos.y = static_cast<size_t>(rand() % windowHeight);
	randPos.y -= static_cast<size_t>(randPos.y) % gridSize;

	// change position
	food.setPosition(randPos);
}

bool Food::checkEaten(const Snake &snake) {
	if (food.getPosition() == snake.getPosition()) {
		return true;
	}

	// if(food.getGlobalBounds().contains(snake.getPosition())){
	// 	return true;
	// }

	return false;
}
