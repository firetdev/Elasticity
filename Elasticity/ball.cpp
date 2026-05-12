#include "ball.hpp"
#include "hsvrgb.hpp"

Ball::Ball(float startX, float startY, float startXVel, float startYVel) {
    x = startX;
    y = startY;
    velocity = {startXVel, startYVel};
    
    shape = sf::CircleShape(15.f);
}

void Ball::render(sf::RenderWindow& win) {
    shape.setPosition(sf::Vector2f(x - 15.f, y - 15.f));
    win.draw(shape);
}

void Ball::bounce(std::vector<bool> axes) {
    if (axes[0]) {
        velocity[0] = -(0.84f * velocity[0]);
    }
    if (axes[1]) {
        velocity[1] = -(0.84f * velocity[1]);
    }
}

void Ball::move(float dt) {
    x += velocity[0] * dt;
    y += velocity[1] * dt;
}

bool Ball::colliding(Target& target) {
    float xDist = target.x - x;
    float yDist = target.y - y;
    float dist = std::sqrt((xDist * xDist) + (yDist * yDist));
    
    return dist <= 15.f + target.radius;
}

void Ball::tickColor(float dt) {
    hue += 120.f * dt;

    if (hue >= 360.f)
        hue -= 360.f;

    shape.setFillColor(HSVtoRGB(hue, 1.f, 1.f));
}
