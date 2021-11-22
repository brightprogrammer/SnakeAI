#include "food.hpp"
#include "math.hpp"
#include <SFML/System/Vector2.hpp>

// food constructor
Food::Food(const sf::Color& color) {
	foodImg.create(gridSize, gridSize, color);
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

// get food position
const sf::Vector2f& Food::getPosition(){
	return food.getPosition();
}
