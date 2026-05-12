#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "target.hpp"

class Ball {
private:
    float hue = 0.f;
    sf::CircleShape shape;
    
    float shockForce = 560.f;
    float radius = 15.f;
    float elasticity = 0.84f;
    float gravityBonus = 1.25;

public:
    float x;
    float y;
    std::vector<float> velocity;
    
    Ball(float, float, float, float);
    
    void render(sf::RenderWindow&);
    void bounce(std::vector<bool>);
    void move(float);
    void tickColor(float);
    void shockwave(sf::Vector2f);
    bool colliding(Target&);
};
