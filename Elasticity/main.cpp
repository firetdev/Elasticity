#include <SFML/Graphics.hpp>
#include <iostream>
#include "ball.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Elasticity", sf::Style::Titlebar | sf::Style::Close);
    
    float gravity = 400.f;
    
    Ball ball(100, 100, 250, 0);
    
    sf::Font font;
    
    if (!font.openFromFile("Anonymous_Pro 2.ttf"))
        std::cout << "Failed to load font\n";
    
    sf::Clock clock;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        float dt = clock.restart().asSeconds();
        
        if (ball.y < 569)
            ball.velocity[1] += gravity * dt;
        
        ball.tickColor(dt);
        ball.move(dt);
        
        std::vector<bool> axes = {false, false};
        
        if (ball.x < 0) {
            axes[0] = true;
            ball.x = 1;
        }
        if (ball.x > 770) {
            axes[0] = true;
            ball.x = 769;
        }
        if (ball.y < 0) {
            axes[1] = true;
            ball.y = 1;
        }
        if (ball.y > 570) {
            axes[1] = true;
            ball.y = 569;
        }
        
        ball.bounce(axes);

        window.clear();
        ball.render(window);
        window.display();
    }
}
