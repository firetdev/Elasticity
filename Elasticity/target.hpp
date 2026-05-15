#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Target {
private:
    float timer = 0.5f;
    float hue = 0.f;
    
    sf::CircleShape shape;

public:
    float x;
    float y;
    float radius = 30.f;
    float shrinkSpeed = 10.f;
    float bonus;
    
    bool alive = true;
    
    Target(float, float, float);
    
    void render(sf::RenderWindow&);
    void tick(float);
};
