/**
   @file snake.hpp
   @date 21/11/21
   @author brightprogrammer
   @brief declares the snake class, our player
 */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "common.hpp"
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

	// move snake
	void move(float xoff, float yoff);

	// draw this snake to given window
	void drawSelf(sf::RenderWindow &window);

  // handle event/input
	void handleEvent(const sf::Event &event);

private:
	sf::Image snakeBodyBlockImg;
	sf::Texture snakeBodyTexture;
	sf::Sprite snakeHead;
	std::vector<sf::Sprite> snakeBody;
	sf::Color snakeHeadColor = sf::Color::Red;
	Direction previousDirection, currentDirection;
};

#endif//SNAKE_HPP
