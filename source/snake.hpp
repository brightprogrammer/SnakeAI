/**
   @file snake.hpp
   @date 21/11/21
   @author brightprogrammer
   @brief declares the snake class, our player
 */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "common.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

// directions in which the snake can move
enum class Direction{
	Up, Down, Left, Right
};

// snake
class Snake {
public:
	// ctor
	Snake();

	// change snake position
	void setPosition(float x, float y);

	// get snake position
	const sf::Vector2f&  getPosition() const;

	// move snake
	void move(float xoff, float yoff);

	// update self position
	void updatePosition();

	// draw this snake to given window
	void drawSelf(sf::RenderWindow &window);

	// handle event/input
	void handleEvent(const sf::Event &event);

	// add a body element to self
	void addBodyElement();

	// check if snake is ok
	bool isOk(){ return bIsOk; }
private:
	sf::Image snakeBodyBlockImg;
	sf::Texture snakeBodyTexture;
	sf::Sprite snakeHead;
	sf::Sprite bodyElement;
	std::vector<sf::Sprite> snakeBody;
	sf::Color snakeHeadColor = sf::Color::Red;
	Direction currentDirection;
	bool bIsOk = true;
};

#endif//SNAKE_HPP
