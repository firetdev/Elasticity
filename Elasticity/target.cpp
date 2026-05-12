#include "target.hpp"
#include "hsvrgb.hpp"

Target::Target(float startX, float startY) {
    x = startX;
    y = startY;
    radius = 30.f;
    
    shape = sf::CircleShape(30.f);
}

void Target::render(sf::RenderWindow& win) {
    shape.setPosition(sf::Vector2f(x - radius, y - radius));
    shape.setRadius(radius);
    win.draw(shape);
}

void Target::tick(float dt) {
    radius -= 15.f * dt;
    hue += 120.f * dt;

    if (hue >= 360.f)
        hue -= 360.f;

    shape.setFillColor(HSVtoRGB(hue, 1.f, 1.f));
}
