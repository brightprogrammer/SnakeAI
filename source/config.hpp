/**
   @file config.hpp
   @date 21/11/21
   @author brightprogrammer
   @brief Our config variables for the Game and AI
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstddef>
#include <string>

// window config variables
constexpr size_t windowWidth = 960;
constexpr size_t windowHeight = 540;
const std::string windowTitle = "Snake AI";

// game config variables
constexpr size_t gridSize = 10;
constexpr float stepSize = static_cast<float>(gridSize);

#endif//CONFIG_HPP
