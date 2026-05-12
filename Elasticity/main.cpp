#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Elasticity", sf::Style::Titlebar | sf::Style::Close);
    sf::CircleShape shape(15.f);
    shape.setFillColor(sf::Color::Green);
    
    sf::Font font;

    if (!font.openFromFile("Anonymous_Pro 2.ttf"))
        std::cout << "Failed to load font\n";


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
