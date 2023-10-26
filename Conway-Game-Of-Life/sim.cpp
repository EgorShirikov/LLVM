#include <SFML/Graphics.hpp>
#include <cassert>
#include "sim.h"

#define DELAY 200

static sf::RenderWindow win;
static sf::Clock cl;
static sf::Event event;
static float t = 0;
static float u = 0.05f;

void simSetPixel(unsigned x, unsigned y, unsigned argb) {
    assert(0 <= x && x < SIM_X_SIZE && "X out of range");
    assert(0 <= y && y < SIM_Y_SIZE && "Y out of range");
    sf::RectangleShape shape;
    uint8_t a = argb >> 24;
    uint8_t r = (argb >> 16) & 255;
    uint8_t g = (argb >> 8) & 255;
    uint8_t b = (argb >> 0) & 255;
    shape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    shape.setPosition((float)x * CELL_SIZE, (float)y * CELL_SIZE);
    shape.setFillColor(sf::Color(r, g, b, a));
    win.draw(shape);
}

bool simEvent() {
    return !(win.pollEvent(event) && event.type == sf::Event::Closed
            || event.key.code == sf::Keyboard::Escape);
}

void simFlush() {
    float deltaTimer = cl.restart().asSeconds();
    t += deltaTimer;
    if (t > u) {
        win.display();
        sf::sleep(sf::milliseconds(DELAY));
        t = 0;
    }
}

void simInit() {
    win.create(sf::VideoMode(WIDTH,
                             HEIGHT),
               "Game of Life");
    srand(std::time(nullptr));
}

void simExit() {
    win.close();
}

int simRand() {
   return rand() % 2;
}


