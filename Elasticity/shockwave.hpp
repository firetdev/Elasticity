#pragma once

#include <SFML/Graphics.hpp>

class Shockwave {
private:
    sf::Vector2f position;
    float growSpeed = 2000.f;
    float fadeSpeed = 1500.f;
    float transparency = 255.f;
    
    sf::CircleShape shape;
    
public:
    float radius = 1.f;
    float maxRadius = 300.f;
    
    Shockwave(sf::Vector2f);
    
    void render(sf::RenderWindow&);
    void tick(float);
};
