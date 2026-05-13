#include "shockwave.hpp"

Shockwave::Shockwave(sf::Vector2f pos) {
    position = pos;
    
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition({pos.x - radius, pos.y - radius});
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
}

void Shockwave::render(sf::RenderWindow& win) {
    shape.setOutlineColor(sf::Color(255, 255, 255, transparency));
    shape.setRadius(radius);
    shape.setPosition({position.x - radius, position.y - radius});
    win.draw(shape);
}

void Shockwave::tick(float dt) {
    radius += growSpeed * dt;
    transparency -= fadeSpeed * dt;
}
