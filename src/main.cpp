#include <SFML/Graphics.hpp>

#include <astre.h>

int main() {

    astre soleil({0.f, 0.f}, {0.f, 0.f}, 1000.f, 50.f, sf::Color::Yellow);

    astre mercure({-100.f, -100.f}, {0.f, 0.f}, 10.f, 2.f, sf::Color::Magenta);
    astre venus({-100.f, 100.f}, {0.f, 0.f}, 10.f, 2.f, sf::Color::White);
    astre terre({100.f, -100.f}, {0.f, 0.f}, 10.f, 2.f, sf::Color::Blue);
    astre mars({100.f, 100.f}, {0.f, 0.f}, 10.f, 2.f, sf::Color::Red);

    float window_width = 1000.f;
    float window_height = 850.f;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(window_width), static_cast<unsigned>(window_height)}), "S0L4R");
    window.setFramerateLimit(60);

    sf::View camera({0.f, 0.f}, {window_width, window_height});

    window.setView(camera);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();

        soleil.draw(window);
        mercure.draw(window);
        venus.draw(window);
        terre.draw(window);
        mars.draw(window);

        window.display();
    }
    return 0;
}