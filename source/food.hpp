#ifndef FOOD_HPP
#define FOOD_HPP

#include "common.hpp"

class Food {
public:
	Food(const sf::Color& color = sf::Color::Green);

  // draw self to given window
	void drawSelf(sf::RenderWindow &window);

	// reset self position to a random one
	void resetPosition();

	// get food position
	const sf::Vector2f& getPosition();
private:
	sf::Image foodImg;
	sf::Texture foodTexture;
	sf::Sprite food;
};

#endif//FOOD_HPP
