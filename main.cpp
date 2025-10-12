#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <optional>
#include <iostream>

int main() {

    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "SFML 3 Window");
    sf::CircleShape shape(50.f);
     shape.setOrigin(sf::Vector2f{shape.getRadius(), shape.getRadius()});
    window.clear(sf::Color::Black);
    shape.setFillColor(sf::Color(0,0,0));
    shape.setPosition({400.f, 300.f});
    window.draw(shape);
    window.display();
    
 


    while (window.isOpen()) {
        // SFML 3: pollEvent returns std::optional<Event>
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event->is<sf::Event::KeyPressed>()) {
                const auto* key = event->getIf<sf::Event::KeyPressed>();
                if (key && key->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }

                    if (event->is<sf::Event::Resized>()){
                const auto* resized = event->getIf<sf::Event::Resized>();
                std::cout<<" rezized" << std::endl;
                window.setView(sf::View(sf::FloatRect(sf::Vector2f{0.f, 0.f},
                     sf::Vector2f{(float)resized->size.x, (float)resized->size.y})));

                window.clear(sf::Color::Black);
                shape.setPosition({resized -> size.x * 0.5f ,resized -> size.y* 0.5f});
                std::cout<<resized -> size.x << std::endl;
                window.draw(shape);
                window.display();

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                // left mouse button is pressed: shoot
                shape.setFillColor(sf::Color(shape.getFillColor().r + 1,shape.getFillColor().g + 10,shape.getFillColor().b + 50));
                window.draw(shape);
                window.display();
            }
        }
    }

    return 0;
}
