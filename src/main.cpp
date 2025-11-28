#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>


#include <astre.h>
#include <iostream>

#include "physique.h"

int main() {

    std::vector<astre> systemeSolaire;

    astre soleil({0.f, 0.f}, {0.f, 0.f}, 10000.f, 40.f, sf::Color::Yellow);

    auto creerPlanete = [&](float distance, float masse, float rayon, sf::Color couleur) {
        sf::Vector2f pos = {-distance, 0.f};
        float vY = std::sqrt((physique::G * soleil.masse) / distance);
        sf::Vector2f vit = {0.f, vY};
        systemeSolaire.push_back(astre(pos, vit, masse, rayon, couleur));
    };

    systemeSolaire.push_back(soleil);
    creerPlanete(70.f,  1.f,  4.f,  sf::Color(169, 169, 169));
    creerPlanete(120.f, 2.f, 8.f,  sf::Color(245, 245, 220));
    creerPlanete(180.f, 5.f, 9.f,  sf::Color::Blue);
    creerPlanete(250.f, 2.f,  6.f,  sf::Color::Red);
    creerPlanete(400.f, 10.f, 25.f, sf::Color(255, 165, 0));

    float window_width = 1000.f;
    float window_height = 850.f;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(window_width), static_cast<unsigned>(window_height)}), "S0L4R");
    window.setFramerateLimit(60);

    sf::View camera({0.f, 0.f}, {window_width, window_height});

    window.setView(camera);


    float dt = 1.f;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        physique::appliquerGravite(systemeSolaire, dt);

        camera.setCenter(systemeSolaire[0].position);
        window.setView(camera);

        window.clear();

        for(auto& a : systemeSolaire) {
            a.draw(window);
        }

        window.display();
    }
    return 0;
}
