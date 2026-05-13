#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "target.hpp"

class Ball {
private:
    float hue = 0.f;
    sf::CircleShape shape;
    
    float shockForce = 600.f;
    float radius = 15.f;
    float elasticity = 0.84f;
    float gravityBonus = 1.3;

public:
    float x;
    float y;
    sf::Vector2f velocity;
    
    Ball(float, float, float, float);
    
    void render(sf::RenderWindow&);
    void bounce(std::vector<bool>);
    void move(float);
    void tickColor(float);
    void shockwave(sf::Vector2f);
    bool colliding(Target&);
    float getTotalVelocity();
};
