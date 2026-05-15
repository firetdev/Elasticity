#include <random>
#include "target.hpp"
#include "hsvrgb.hpp"

Target::Target(float startX, float startY, float score) {
    x = startX;
    y = startY;
    bonus = score / 8;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> hueDist(0.f, 360.f);
    hue = hueDist(gen);
    
    shape = sf::CircleShape(radius);
}

void Target::render(sf::RenderWindow& win) {
    shape.setPosition(sf::Vector2f(x - radius, y - radius));
    shape.setRadius(radius);
    win.draw(shape);
}

void Target::tick(float dt) {
    if (timer <= 0) {
        float shrinkTotal = (shrinkSpeed + bonus < 20.f) ? shrinkSpeed + bonus : 20.f;
        radius -= shrinkTotal * dt;
        hue += 120.f * dt;
        
        if (hue >= 360.f)
            hue -= 360.f;
    } else {
        timer -= dt;
    }
    
    shape.setFillColor(HSVtoRGB(hue, 1.f, 1.f));
}
