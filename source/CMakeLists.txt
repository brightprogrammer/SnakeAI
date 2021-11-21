# find all cpp files recursively
file(GLOB_RECURSE GAME_SRCS ${CMAKE_CURRENT_SOURCE_DIRECTORY} *.cpp)

# setup main exeutable
add_executable(snake ${GAME_SRCS})
target_link_libraries(snake sfml-graphics sfml-system sfml-window)
