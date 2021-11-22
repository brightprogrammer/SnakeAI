#include "common.hpp"
#include "config.hpp"
#include "snake.hpp"
#include <SFML/System/Vector2.hpp>

Snake::Snake(){
	// create texture for snake head and body
	snakeBodyBlockImg.create(gridSize, gridSize, sf::Color::White);
	snakeBodyTexture.loadFromImage(snakeBodyBlockImg);

	// create snake head sprite
	snakeHead.setTexture(snakeBodyTexture);
	snakeHead.setColor(snakeHeadColor);

	// set initial position
	sf::Vector2f randPos;
	randPos.x = static_cast<size_t>(rand() % windowWidth);
	randPos.x -= static_cast<size_t>(randPos.x) % gridSize;
	randPos.y = static_cast<size_t>(rand() % windowHeight);
	randPos.y -= static_cast<size_t>(randPos.y) % gridSize;
	snakeHead.setPosition(randPos);

	// set initial directions
	currentDirection = Direction::Up;

	// setup snake body
	size_t bodySize = 1;

	// setup body element sprite
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

// get position of snake head
const sf::Vector2f& Snake::getPosition() const{
	return snakeHead.getPosition();
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

	// check whether the snake crossed the boundary
	const sf::Vector2f& snakePos =  snakeHead.getPosition();
	sf::Vector2f newPos = snakePos;

	if(snakePos.x > windowWidth){
		newPos.x = gridSize;
	}else if(snakePos.x < 0){
		newPos.x = windowWidth - windowWidth % gridSize;
	}else if(snakePos.y > windowHeight){
		newPos.y = gridSize;
	}else if(snakePos.y < 0){
		newPos.y = windowHeight - windowHeight % gridSize;
	}

	// update position
	snakeHead.setPosition(newPos);
}

// update self position
void Snake::updatePosition(){
	// keep moving snake body
	switch (currentDirection) {
	case Direction::Up:
		move(0, -stepSize);
		break;
	case Direction::Down:
		move(0, stepSize);
		break;
	case Direction::Left:
		move(-stepSize, 0);
		break;
	case Direction::Right:
		move(stepSize, 0);
		break;
	}

	// check if snake ate itself
	for(const auto& bodyElem : snakeBody){
		if(bodyElem.getGlobalBounds().contains(snakeHead.getPosition())){
			bIsOk = false;
			snakeBody.erase(snakeBody.begin()+1, snakeBody.end());
		}
	}
}

// draw snake body ingiven window
void Snake::drawSelf(sf::RenderWindow &window) {
	updatePosition();

	window.draw(snakeHead);
	for(const auto& bodyElement : snakeBody){
		window.draw(bodyElement);
	}
}

// handle events and move snake
void Snake::handleEvent(const sf::Event &event){
	// update snake position and currentDirection
	if (event.key.code == sf::Keyboard::W && currentDirection != Direction::Down) { // up
		move(0, -stepSize);
		currentDirection = Direction::Up;
	} else if (event.key.code == sf::Keyboard::A && currentDirection != Direction::Right) { // left
		move(-stepSize, 0);
		currentDirection = Direction::Left;
	} else if (event.key.code == sf::Keyboard::S && currentDirection != Direction::Up) { // down
		move(0, stepSize);
		currentDirection = Direction::Down;
	} else if (event.key.code == sf::Keyboard::D && currentDirection != Direction::Left) { // right
		move(stepSize, 0);
		currentDirection = Direction::Right;
	}
}

void Snake::addBodyElement(){
	snakeBody.push_back(bodyElement);
	updatePosition();
}
