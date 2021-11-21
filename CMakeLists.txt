# our cmake version
cmake_minimum_required(VERSION 3.5)

# project settings
project(SnakeAI VERSION 0.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# project structure
add_subdirectory(source)
