#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>


#include <astre.h>
#include <iostream>

#include "physique.h"

int main() {

    std::vector<astre> systemeSolaire;

    const float AL = 1500.f;
    const float MASSE_TERRE = 10.f;

    astre soleil({0.f, 0.f}, {0.f, 0.f}, 300000.f * MASSE_TERRE, 30.f, sf::Color::Yellow);    systemeSolaire.push_back(soleil);

    auto creerPlanete = [&](float distanceAU, float masseRatioTerre, float rayonVisuel, sf::Color couleur) {
        float distancePixels = distanceAU * AL;
        sf::Vector2f pos = {-distancePixels, 0.f};
        float masseReelle = masseRatioTerre * MASSE_TERRE;
        float vY = std::sqrt((physique::G * soleil.masse) / distancePixels);
        sf::Vector2f vit = {0.f, vY};

        systemeSolaire.push_back(astre(pos, vit, masseReelle, rayonVisuel, couleur));
    };


    creerPlanete(0.39f, 0.055f, 3.f, sf::Color(169, 169, 169));
    creerPlanete(0.72f, 0.815f, 5.f, sf::Color(245, 245, 220));

    creerPlanete(1.0f, 5.0f, 5.f, sf::Color(0, 0, 255));

    astre& terreRef = systemeSolaire.back();
    float distTerreLune = 0.015f * AL;
    sf::Vector2f posLune = terreRef.position + sf::Vector2f{-distTerreLune, 0.f};
    float vLune = std::sqrt((physique::G * terreRef.masse) / distTerreLune);
    sf::Vector2f vitLune = terreRef.vitesse + sf::Vector2f{0.f, vLune};

    systemeSolaire.push_back(astre(posLune, vitLune, 0.012f * MASSE_TERRE, 2.f, sf::Color::White));

    creerPlanete(1.52f, 0.107f, 4.f, sf::Color(255, 69, 0));
    creerPlanete(5.2f, 317.8f, 18.f, sf::Color(210, 105, 30));
    creerPlanete(9.58f, 95.1f, 15.f, sf::Color(244, 196, 48));
    creerPlanete(19.22f, 14.5f, 10.f, sf::Color(0, 255, 255));
    creerPlanete(30.05f, 17.1f, 10.f, sf::Color(0, 0, 139));
    creerPlanete(39.0f, 0.01f, 2.f, sf::Color(200, 200, 200));

    float window_width = 1400.f;
    float window_height = 1000.f;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(window_width), static_cast<unsigned>(window_height)}), "S0L4R");
    window.setFramerateLimit(144);

    sf::View camera({0.f, 0.f}, {window_width, window_height});
    camera.zoom(2.5f);
    window.setView(camera);


    float dt = 0.01f;

   float vitesseCamera = 20.f;

    bool verouillage = true;
    int indexCible = 0;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (wheel->delta > 0) camera.zoom(0.9f);
                else camera.zoom(1.1f);
            }



            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {

                if (key->code == sf::Keyboard::Key::E) {
                    dt *= 1.5f;
                }
                if (key->code == sf::Keyboard::Key::A) {
                    dt /= 1.5f;
                    if (dt < 0.01f) dt = 0.01f;
                }

                if (key->code == sf::Keyboard::Key::Space) { verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num1 || key->code == sf::Keyboard::Key::Numpad1) { indexCible = 0; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num2 || key->code == sf::Keyboard::Key::Numpad2) { indexCible = 1; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num3 || key->code == sf::Keyboard::Key::Numpad3) { indexCible = 2; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num4 || key->code == sf::Keyboard::Key::Numpad4 || key->code == sf::Keyboard::Key::Apostrophe) { indexCible = 3; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num5 || key->code == sf::Keyboard::Key::Numpad5) { indexCible = 4; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num6 || key->code == sf::Keyboard::Key::Numpad6 || key->code == sf::Keyboard::Key::Hyphen) { indexCible = 5; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num7 || key->code == sf::Keyboard::Key::Numpad7) { indexCible = 6; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num8 || key->code == sf::Keyboard::Key::Numpad8) { indexCible = 7; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num9 || key->code == sf::Keyboard::Key::Numpad9) { indexCible = 8; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num0 || key->code == sf::Keyboard::Key::Numpad0) { indexCible = 9; verouillage = true; }
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))  { camera.move({-vitesseCamera, 0.f}); verouillage = false; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { camera.move({vitesseCamera, 0.f});  verouillage = false; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))    { camera.move({0.f, -vitesseCamera}); verouillage = false; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))  { camera.move({0.f, vitesseCamera});  verouillage = false; }

        for(int i=0; i<4; i++) {
            physique::appliquerGravite(systemeSolaire, dt / 4.f);
        }

        if (verouillage) {
            if (indexCible >= 0 && indexCible < systemeSolaire.size()) {
                camera.setCenter(systemeSolaire[indexCible].position);
            }
        }

        window.setView(camera);

        window.clear();
        for(auto& a : systemeSolaire) {
            a.draw(window);
        }
        window.display();
    }
    return 0;
}