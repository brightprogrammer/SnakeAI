#ifndef MATH_HPP
#define MATH_HPP

#include "common.hpp"
#include <cmath>
#include <math.h>

// get distance between two points
inline float getDistance(const sf::Vector2f p1, const sf::Vector2f &p2) {
	return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
} 

#endif//MATH_HPP
