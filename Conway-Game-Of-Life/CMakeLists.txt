cmake_minimum_required(VERSION 3.26)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES sim.cpp
        sim.h
        life.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(GameOfLife
        ${SOURCE_FILES})

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(GameOfLife sfml-system sfml-window sfml-graphics sfml-audio sfml-network)