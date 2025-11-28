#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <memory>

#include <astre.h>
#include <physique.h>

int trouverPlaneteSousSouris(sf::RenderWindow& window, const std::vector<astre>& astres) {
    sf::Vector2i mousePosScreen = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosScreen);
    for (size_t i = 0; i < astres.size(); ++i) {
        float rayonClic = astres[i].forme.getRadius();
        if (rayonClic < 50.f) rayonClic = 50.f;
        sf::Vector2f diff = astres[i].position - mousePosWorld;
        float distSq = diff.x * diff.x + diff.y * diff.y;

        if (distSq < rayonClic * rayonClic) {
            return (int)i;
        }
    }
    return -1;
}

int main() {
    std::vector<astre> systemeSolaire;
    const float PXL_TERRE = 1.0f;
    const float AU = 23455.f * PXL_TERRE;
    const float MASSE_TERRE = 10.f;
    astre soleil({0.f, 0.f}, {0.f, 0.f}, 333000.f * MASSE_TERRE, 109.f * PXL_TERRE, sf::Color::Yellow);
    systemeSolaire.push_back(soleil);
    auto creerPlanete = [&](float distanceAU, float masseRatioTerre, float rayonRatioTerre, sf::Color couleur) {
        float distancePixels = distanceAU * AU;
        sf::Vector2f pos = {-distancePixels, 0.f};
        float masseReelle = masseRatioTerre * MASSE_TERRE;
        float vY = std::sqrt((physique::G * soleil.masse) / distancePixels);
        sf::Vector2f vit = {0.f, vY};
        systemeSolaire.push_back(astre(pos, vit, masseReelle, rayonRatioTerre * PXL_TERRE, couleur));
    };
    creerPlanete(0.39f, 0.055f, 0.38f, sf::Color(169, 169, 169));
    creerPlanete(0.72f, 0.815f, 0.95f, sf::Color(245, 245, 220));
    creerPlanete(1.0f, 1.0f, 1.0f, sf::Color(0, 0, 255));
    astre& terreRef = systemeSolaire.back();
    float distTerreLune = 60.f * PXL_TERRE;
    sf::Vector2f posLune = terreRef.position + sf::Vector2f{-distTerreLune, 0.f};
    float vLune = std::sqrt((physique::G * terreRef.masse) / distTerreLune);
    sf::Vector2f vitLune = terreRef.vitesse + sf::Vector2f{0.f, vLune};
    systemeSolaire.push_back(astre(posLune, vitLune, 0.012f * MASSE_TERRE, 0.27f * PXL_TERRE, sf::Color::White));
    creerPlanete(1.52f, 0.107f, 0.53f, sf::Color(255, 69, 0));
    creerPlanete(5.2f, 317.8f, 11.2f, sf::Color(210, 105, 30));
    creerPlanete(9.58f, 95.1f, 9.45f, sf::Color(244, 196, 48));
    creerPlanete(19.22f, 14.5f, 4.0f, sf::Color(0, 255, 255));
    creerPlanete(30.05f, 17.1f, 3.88f, sf::Color(0, 0, 139));
    creerPlanete(39.0f, 0.002f, 0.18f, sf::Color(200, 200, 200));
    float window_width = 1400.f;
    float window_height = 1000.f;
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(window_width), static_cast<unsigned>(window_height)}), "S0L4R - REAL SCALE");
    window.setFramerateLimit(144);
    sf::View camera({0.f, 0.f}, {window_width, window_height});
    camera.zoom(1.0f);
    window.setView(camera);
    float dt = 1.f;
    float vitesseCamera = 1000.f;
    bool verouillage = true;
    int indexCible = 0;
    std::unique_ptr<sf::RenderWindow> windowInspecteur = nullptr;
    int indexInspecte = -1;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseBtn->button == sf::Mouse::Button::Left) {
                    int id = trouverPlaneteSousSouris(window, systemeSolaire);
                    if (id != -1) {
                        indexInspecte = id;
                        if (!windowInspecteur) {
                            windowInspecteur = std::make_unique<sf::RenderWindow>(
                                sf::VideoMode({400, 400}), "Inspecteur", sf::Style::Titlebar | sf::Style::Close
                            );
                        }
                        windowInspecteur->requestFocus();
                    }
                }
            }
            if (const auto* wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (wheel->delta > 0) {
                    camera.zoom(0.8f);
                    vitesseCamera *= 0.8f;
                } else {
                    camera.zoom(1.2f);
                    vitesseCamera *= 1.2f;
                }
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
                if (key->code == sf::Keyboard::Key::Num5 || key->code == sf::Keyboard::Key::Numpad5) { indexCible = 5; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num6 || key->code == sf::Keyboard::Key::Numpad6 || key->code == sf::Keyboard::Key::Hyphen) { indexCible = 6; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num7 || key->code == sf::Keyboard::Key::Numpad7) { indexCible = 7; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num8 || key->code == sf::Keyboard::Key::Numpad8) { indexCible = 8; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num9 || key->code == sf::Keyboard::Key::Numpad9) { indexCible = 9; verouillage = true; }
                if (key->code == sf::Keyboard::Key::Num0 || key->code == sf::Keyboard::Key::Numpad0) { indexCible = 10; verouillage = true; }
            }
        }
        if (windowInspecteur && windowInspecteur->isOpen()) {
            while (const std::optional eventPop = windowInspecteur->pollEvent()) {
                if (eventPop->is<sf::Event::Closed>()) {
                    windowInspecteur->close();
                    windowInspecteur = nullptr;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))  { camera.move({-vitesseCamera, 0.f}); verouillage = false; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { camera.move({vitesseCamera, 0.f});  verouillage = false; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))    { camera.move({0.f, -vitesseCamera}); verouillage = false; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))  { camera.move({0.f, vitesseCamera});  verouillage = false; }
        for(int i=0; i<32; i++) {
            physique::appliquerGravite(systemeSolaire, dt / 32.f);
        }
        if (verouillage) {
            if (indexCible >= 0 && indexCible < systemeSolaire.size()) {
                camera.setCenter(systemeSolaire[indexCible].position);
            }
        }
        window.setView(camera);
        window.clear();
        for(auto& a : systemeSolaire) {
            float distCam = std::sqrt(std::pow(a.position.x - camera.getCenter().x, 2) + std::pow(a.position.y - camera.getCenter().y, 2));
            a.draw(window);
        }
        window.display();
        if (windowInspecteur && windowInspecteur->isOpen() && indexInspecte != -1) {
            if (indexInspecte < systemeSolaire.size()) {
                windowInspecteur->clear(sf::Color(20, 20, 30));
                sf::CircleShape grosPlan = systemeSolaire[indexInspecte].forme;
                grosPlan.setPosition({200.f, 200.f});
                grosPlan.setRadius(100.f);
                grosPlan.setOrigin({100.f, 100.f});
                windowInspecteur->draw(grosPlan);
                windowInspecteur->display();
            } else {
                windowInspecteur->close();
                windowInspecteur = nullptr;
            }
        }
    }
    return 0;
}