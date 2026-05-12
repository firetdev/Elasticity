#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "target.hpp"

class Ball {
private:
    float hue = 0.f;
    sf::CircleShape shape;

public:
    float x;
    float y;
    std::vector<float> velocity;
    
    Ball(float, float, float, float);
    
    void render(sf::RenderWindow&);
    void bounce(std::vector<bool>);
    void move(float);
    bool colliding(Target&);
    void tickColor(float);
};
