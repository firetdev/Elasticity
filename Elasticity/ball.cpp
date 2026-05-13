#include "ball.hpp"
#include "hsvrgb.hpp"
#include <iostream>

Ball::Ball(float startX, float startY, float startXVel, float startYVel) {
    x = startX;
    y = startY;
    velocity = {startXVel, startYVel};
    
    shape = sf::CircleShape(radius);
}

void Ball::render(sf::RenderWindow& win) {
    shape.setPosition(sf::Vector2f(x - radius, y - radius));
    win.draw(shape);
}

void Ball::bounce(std::vector<bool> axes) {
    if (axes[0]) {
        velocity.x = -(elasticity * velocity.x);
    }
    if (axes[1]) {
        velocity.y = -(elasticity * velocity.y);
    }
}

void Ball::move(float dt) {
    x += velocity.x * dt;
    y += velocity.y * dt;
}

void Ball::tickColor(float dt) {
    hue += 120.f * dt;

    if (hue >= 360.f)
        hue -= 360.f;

    shape.setFillColor(HSVtoRGB(hue, 1.f, 1.f));
}

void Ball::shockwave(sf::Vector2f pos) {
    float xDist = pos.x - x;
    float yDist = pos.y - y;
    float dist = std::sqrt((xDist * xDist) + (yDist * yDist));
    float ratio = std::abs(xDist) / std::abs(yDist);
    
    float force = shockForce - std::abs(dist);
    if (force < 10) return;
    
    float fractionalForce = force / (ratio + 1);
    
    if (xDist < 0)
        velocity.x += fractionalForce * ratio;
    else
        velocity.x -= fractionalForce * ratio;
    if (yDist < 0)
        velocity.y += fractionalForce;
    else
        velocity.y -= fractionalForce * gravityBonus;
}

bool Ball::colliding(Target& target) {
    float xDist = target.x - x;
    float yDist = target.y - y;
    float dist = std::sqrt((xDist * xDist) + (yDist * yDist));
    
    return dist <= radius + target.radius;
}

float Ball::getTotalVelocity() {
    return std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
}
