#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Target {
private:
    float hue = 0.f;
    sf::CircleShape shape;

public:
    float x;
    float y;
    float radius;
    
    Target(float, float);
    
    void render(sf::RenderWindow&);
    void tick(float);
};
