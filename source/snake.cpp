#include "common.hpp"
#include "snake.hpp"

Snake::Snake(){
	// create texture for snake head and body
	snakeBodyBlockImg.create(gridSize, gridSize, sf::Color::White);
	snakeBodyTexture.loadFromImage(snakeBodyBlockImg);

	// create snake head sprite
	snakeHead.setTexture(snakeBodyTexture);
	snakeHead.setColor(snakeHeadColor);

	// set initial position
	snakeHead.setPosition(windowWidth / 2.0, windowHeight / 2.0);

	// set initial directions
	currentDirection = Direction::Up;
	previousDirection = Direction::Up;

	// setup snake body
	size_t bodySize = 8;

	// setup body element sprite
	sf::Sprite bodyElement;
	bodyElement.setTexture(snakeBodyTexture);

	for(size_t i = 0; i < bodySize; i++){
		bodyElement.setPosition(snakeHead.getPosition() + sf::Vector2f(0, stepSize * (i+1)));
		snakeBody.emplace_back(bodyElement);
	}
}

// change position of snake
void Snake::setPosition(float x, float y) {
	snakeHead.setPosition(x, y);
}

// move snake
void Snake::move(float xoff, float yoff){
	// update body position
	for(size_t i = snakeBody.size() - 1; i >= 1; i--){
		snakeBody[i].setPosition(snakeBody[i-1].getPosition());
	}
	snakeBody[0].setPosition(snakeHead.getPosition());

	// update head position
	snakeHead.move(sf::Vector2f(xoff, yoff));
}

// draw snake body in given window
void Snake::drawSelf(sf::RenderWindow &window) {
	// keep moving snake body
	switch(currentDirection){
	case Direction::Up : move(0, -stepSize); break;
	case Direction::Down : move(0, stepSize); break;
	case Direction::Left : move(-stepSize, 0); break;
	case Direction::Right : move(stepSize, 0); break;
	}

	window.draw(snakeHead);
	for(const auto& bodyElement : snakeBody){
		window.draw(bodyElement);
	}
}

// handle events and move snake
void Snake::handleEvent(const sf::Event &event){
	// cache currentDirection in previousDirection
	previousDirection = currentDirection;

	// update snake position and currentDirection
	if (event.key.code == sf::Keyboard::W) { // up
		move(0, -stepSize);
		currentDirection = Direction::Up;
	}else if(event.key.code == sf::Keyboard::A){ // left
		move(-stepSize, 0);
		currentDirection = Direction::Left;
	} else if (event.key.code == sf::Keyboard::S){ // down
		move(0, stepSize);
		currentDirection = Direction::Down;
	} else if (event.key.code == sf::Keyboard::D){ // right 
		move(stepSize, 0);
		currentDirection = Direction::Right;
	}else{
		std::cout << "Unhandled keyboard event" << std::endl;
	}
}
