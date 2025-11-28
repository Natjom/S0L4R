#include "../include/astre.h"
#include <algorithm>

astre::astre() : position(0,0), vitesse(0,0), masse(1.f), rayon(1.f) {
    forme.setRadius(1.f);
    forme.setPosition({0.f, 0.f}); // Correction ici
}

astre::astre(sf::Vector2f pos, sf::Vector2f vit, float m, float r, sf::Color col)
    : position(pos), vitesse(vit), masse(m), rayon(r) {
    forme.setRadius(rayon);
    forme.setFillColor(col);
    forme.setOrigin({rayon, rayon}); // Correction ici
    forme.setPosition(position);
}

void astre::draw(sf::RenderWindow &window) {
    if (trajectoire.size() > 1) {
        sf::VertexArray lines(sf::PrimitiveType::LineStrip, trajectoire.size());
        sf::Color trailColor = forme.getFillColor();
        trailColor.a = 150;

        for (size_t i = 0; i < trajectoire.size(); ++i) {
            lines[i].position = trajectoire[i];
            lines[i].color = trailColor;
        }
        window.draw(lines);
    }

    float zoomFactor = window.getView().getSize().x / window.getSize().x;

    float minRadiusWorld = 3.0f * zoomFactor;

    float radiusToDraw = std::max(rayon, minRadiusWorld);

    forme.setRadius(radiusToDraw);
    forme.setOrigin({radiusToDraw, radiusToDraw}); // Correction ici
    forme.setPosition(position);

    window.draw(forme);
}