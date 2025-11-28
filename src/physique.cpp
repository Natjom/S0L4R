#include "physique.h"

#include <iostream>

void physique::appliquerGravite(std::vector<astre>& astres, float dt) {
    
    for (auto& a : astres) { a.vitesse += {0.f, 0.f}; }

    for (size_t i = 0; i < astres.size(); ++i) {
        for (size_t j = i + 1; j < astres.size(); ++j) {

            astre& astre1 = astres[i];
            astre& astre2 = astres[j];

            sf::Vector2f direction = astre2.position - astre1.position;
            float distSq = direction.x * direction.x + direction.y * direction.y;

            if (distSq < 100.f) continue;

            float dist = std::sqrt(distSq);

            float forceMagnitude = G * (astre1.masse * astre2.masse) / distSq;

            sf::Vector2f forceVector = (direction / dist) * forceMagnitude;

            astre1.vitesse += (forceVector / astre1.masse) * dt;
            astre2.vitesse -= (forceVector / astre2.masse) * dt;
        }
    }

    for (auto& a : astres) {
        a.position += a.vitesse * dt;
    }
}