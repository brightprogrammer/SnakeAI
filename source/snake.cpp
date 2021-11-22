#include "common.hpp"
#include "config.hpp"
#include "snake.hpp"
#include <SFML/System/Vector2.hpp>

sf::Color operator * (const sf::Color& color, float factor){
	return sf::Color(color.r * factor, color.g * factor, color.b * factor, color.a);
}

Snake::Snake(Food& food) : food(food){
	// create texture for snake head and body
	snakeBodyBlockImg.create(gridSize, gridSize, sf::Color::White);
	snakeBodyTexture.loadFromImage(snakeBodyBlockImg);

	// create snake head sprite
	snakeHead.setTexture(snakeBodyTexture);
	snakeHead.setColor(snakeHeadColor * colorGrad);

	colorGrad -= colorDecayFactor;

	// set initial position
	sf::Vector2f randPos;
	randPos.x = static_cast<uint32_t>(rand() % windowWidth);
	randPos.x -= static_cast<uint32_t>(randPos.x) % gridSize;
	randPos.y = static_cast<uint32_t>(rand() % windowHeight);
	randPos.y -= static_cast<uint32_t>(randPos.y) % gridSize;
	snakeHead.setPosition(randPos);

	// set initial directions
	currentDirection = Direction::Up;

	// setup body element sprite
	bodyElement.setTexture(snakeBodyTexture);

	for(size_t i = 0; i < snakeInitialSize; i++){
		bodyElement.setColor(snakeHeadColor * colorGrad);
		colorGrad -= colorDecayFactor;
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

// snap snake's position to grid
void Snake::reflectBackToWindow(){
	// check whether the snake crossed the boundary
	const sf::Vector2f &snakePos = snakeHead.getPosition();
	sf::Vector2f newPos = snakePos;

	if (snakePos.x > windowWidth) {
		newPos.x = 0;
	} else if (snakePos.x < 0) {
		newPos.x = windowWidth;
	} else if (snakePos.y > windowHeight){
		newPos.y = 0;
	} else if (snakePos.y < 0) {
		newPos.y = windowHeight;
	}

	// update position
	snakeHead.setPosition(newPos);
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

	// reflect position to window
	reflectBackToWindow();

	// check if food was eaten after each move!
	// it is necessary for the function to be present here!
	if(snakeHead.getPosition() == food.getPosition()){
		++score;
		addBodyElement();
		food.resetPosition();
	}

	// check if snake ate itself after each move
	// it is necessary for this function to be present here!
	for (const auto &bodyElem : snakeBody) {
		if (bodyElem.getPosition() == snakeHead.getPosition()) {
			score = 0;
            snakeBody.erase(snakeBody.begin() + snakeInitialSize, snakeBody.end());
		}
	}
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
}

// draw snake body ingiven window
void Snake::drawSelf(sf::RenderWindow &window) {
	window.draw(snakeHead);
	for(const auto& bodyElement : snakeBody){
		window.draw(bodyElement);
	}

	updatePosition();
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
	bodyElement.setColor(snakeHeadColor * colorGrad);
	colorGrad -= colorDecayFactor;
	bodyElement.setPosition(snakeBody.back().getPosition());
	snakeBody.push_back(bodyElement);
	// updatePosition();
}
