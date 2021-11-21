#ifndef FOOD_HPP
#define FOOD_HPP

#include "common.hpp"
#include "snake.hpp"

class Food {
public:
  Food();

  // draw self to given window
  void drawSelf(sf::RenderWindow &window);

  // reset self position to a random one
  void resetPosition();

  // check whether snake had the food or not
  bool checkEaten(const Snake &snake);

private:
  sf::Image foodImg;
  sf::Texture foodTexture;
  sf::Sprite food;
};

#endif//FOOD_HPP
