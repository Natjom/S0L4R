#include "astre.h"

astre::astre() : position(0,0), vitesse(0,0), masse(1.f), rayon(1.f) {
    forme.setRadius(1.f);
}

astre::astre(sf::Vector2f pos, sf::Vector2f vit, float m, float rayon, sf::Color couleur)
    : position(pos), vitesse(vit), masse(m), rayon(rayon), forme(rayon) {

    forme.setFillColor(couleur);
    forme.setOrigin({rayon, rayon});
    forme.setPosition(position);
}

void astre::draw(sf::RenderWindow &window) {
    forme.setPosition(position);
    window.draw(forme);
}