#include "astre.h"

astre::astre(sf::Vector2f pos, sf::Vector2f vit, float m, float rayon, sf::Color couleur)
    : position(pos), vitesse(vit), masse(m), forme(rayon) {

    forme.setFillColor(couleur);
    forme.setOrigin({rayon, rayon});
    forme.setPosition(position);
}

void astre::draw(sf::RenderWindow &window) {
    forme.setPosition(position);
    window.draw(forme);
}