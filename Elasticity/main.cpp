#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include "ball.hpp"
#include "target.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Elasticity", sf::Style::Titlebar | sf::Style::Close);
    
    sf::Font font;
    if (!font.openFromFile("Anonymous_Pro 2.ttf"))
        std::cout << "Failed to load font\n";
    
    float gravity = 350.f;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(30, 770);
    std::uniform_int_distribution<> yDist(30, 570);
    std::uniform_int_distribution<> timerDist(1, 4);
    
    Ball ball(100, 100, 250, 0);
    std::vector<Target> targets;
    
    float time = 0.f;
    int displayTime;
    int clicks = 10;
    
    float timer = 0.f;
    int interval = timerDist(gen);
    
    float deathTimer = 10.5;
    bool dead = false;
    
    sf::Clock clock;
    
    sf::Text timeText(font);
    timeText.setPosition({280, 40});
    sf::Text clicksText(font);
    clicksText.setPosition({480, 40});
    sf::Text deathText(font);
    deathText.setPosition({385, 275});
    deathText.setCharacterSize(50);
    sf::Text retryText(font);
    retryText.setPosition({200, 400});
    retryText.setString("Click to try again");
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (dead) {
                    dead = false;
                    
                    time = 0.f;
                    clicks = 8;
                    
                    timer = 0.f;
                    interval = timerDist(gen);
                    
                    deathTimer = 10.5;
                    
                    targets = {};
                    
                    ball.x = 100;
                    ball.y = 100;
                    ball.velocity = {250, 0};
                } else if (clicks > 0) {
                    clicks--;
                    ball.shockwave(sf::Vector2f(sf::Mouse::getPosition(window)));
                }
            }
        }
        
        if (!dead) {
            float dt = clock.restart().asSeconds();
            timer += dt;
            time += dt;
            if (clicks <= 0)
                deathTimer -= dt;
            else
                deathTimer = 10.5;
            
            displayTime = static_cast<int>(time);
            
            if (timer >= interval) {
                targets.emplace_back(Target(xDist(gen), yDist(gen)));
                timer = 0.f;
                interval = timerDist(gen);
            }
            
            if (deathTimer <= 0.8)
                dead = true;
        
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
                if (target.radius < 0) {
                    time = 0.75f * time;
                    target.alive = false;
                }
                if (ball.colliding(target)) {
                    clicks++;
                    target.alive = false;
                }
            }
            
            targets.erase(
                          std::remove_if(targets.begin(), targets.end(),
                                         [](const Target& t) {
                                             return !t.alive;
                                         }),
                          targets.end()
                          );
            
            timeText.setString(std::to_string(displayTime));
            clicksText.setString(std::to_string(clicks));
            deathText.setString(std::to_string(static_cast<int>(deathTimer)));
        }

        window.clear();
        ball.render(window);
        for (auto& target : targets) {
            target.render(window);
        }
        window.draw(timeText);
        window.draw(clicksText);
        if (clicks <= 0)
            window.draw(deathText);
        if (dead)
            window.draw(retryText);
        window.display();
    }
}
