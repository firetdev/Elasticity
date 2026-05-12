#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "ball.hpp"
#include "target.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Elasticity", sf::Style::Titlebar | sf::Style::Close);
    
    float gravity = 400.f;
    
    Ball ball(100, 100, 250, 0);
    std::vector<Target> targets{Target(380, 300)};
    
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
        
        targets.erase(
            std::remove_if(targets.begin(), targets.end(),
                [](const Target& t) {
                    return !(t.radius > 0);
                }),
            targets.end()
        );
        
        if (ball.y < 584)
            ball.velocity[1] += gravity * dt;
        
        ball.tickColor(dt);
        ball.move(dt);
        
        std::vector<bool> axes = {false, false};
        
        if (ball.x < 15) {
            axes[0] = true;
            ball.x = 16;
        }
        if (ball.x > 785) {
            axes[0] = true;
            ball.x = 784;
        }
        if (ball.y < 15) {
            axes[1] = true;
            ball.y = 16;
        }
        if (ball.y > 585) {
            axes[1] = true;
            ball.y = 584;
        }
        
        ball.bounce(axes);
        
        for (auto& target : targets) {
            target.tick(dt);
        }
        
        targets.erase(
            std::remove_if(targets.begin(), targets.end(),
                [&](Target& target) {
                    return ball.colliding(target);
                }),
            targets.end()
        );

        window.clear();
        ball.render(window);
        for (auto& target : targets) {
            target.render(window);
        }
        window.display();
    }
}
