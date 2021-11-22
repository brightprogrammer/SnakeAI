/**
   @file snake.hpp
   @date 21/11/21
   @author brightprogrammer
   @brief declares the snake class, our player
 */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "common.hpp"
#include "food.hpp"
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
	Snake(Food& food);

	// change snake position
	void setPosition(float x, float y);

	// get snake position
	const sf::Vector2f&  getPosition() const;

	// reflect snake back to window if snake crosses boundary
	void reflectBackToWindow();

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

	// get score
	size_t getScore() { return score; }
private:
	// food that snake needs to catch
	Food& food;

	// texture data
	sf::Image snakeBodyBlockImg;
	sf::Texture snakeBodyTexture;

	// snake's head
	sf::Sprite snakeHead;

	// single body element
	sf::Sprite bodyElement;

	// body of snake
	std::vector<sf::Sprite> snakeBody;

	// color of snake's head
	sf::Color snakeHeadColor = sf::Color(47, 162, 250);

        // begin direction
	Direction currentDirection = Direction::Up;

	// start with 0 score
	size_t score = 0;

	// initial size of sname
	size_t snakeInitialSize = 1;

	// if event was just handled now then we don't need to update
	bool eventHandledJustNow = false;

	// color gradient
	float colorGrad = 1.0f;

	// decay factor
	float colorDecayFactor = 0.001f;
};

#endif//SNAKE_HPP
