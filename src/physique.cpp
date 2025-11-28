#include "physique.h"

#include <iostream>

void physique::appliquerGravite(std::vector<astre>& astres, float dt) {

    std::vector<astre> nouveauxAstres;

    std::vector<bool> estDetruit(astres.size(), false);

    for (auto& a : astres) { a.vitesse += {0.f, 0.f}; }

    for (size_t i = 0; i < astres.size(); ++i) {
        for (size_t j = i + 1; j < astres.size(); ++j) {

            astre& astre1 = astres[i];
            astre& astre2 = astres[j];


            sf::Vector2f direction = astre2.position - astre1.position;
            float distSq = direction.x * direction.x + direction.y * direction.y;
            float dist = std::sqrt(distSq);

            if (dist < (astre1.forme.getRadius() + astre2.forme.getRadius())) {

                // On crée la fusion
                nouveauxAstres.push_back(fusionner(astre1, astre2));

                // On marque les deux parents comme "à supprimer"
                estDetruit[i] = true;
                estDetruit[j] = true;

                // On arrête de calculer la gravité pour ce couple
                continue;
            }

            if (distSq < 0.001f) continue;

            float forceMagnitude = G * (astre1.masse * astre2.masse) / distSq;

            sf::Vector2f forceVector = (direction / dist) * forceMagnitude;

            astre1.vitesse += (forceVector / astre1.masse) * dt;
            astre2.vitesse -= (forceVector / astre2.masse) * dt;
        }
    }

    size_t k = 0;
    for(size_t i = 0; i < astres.size(); ++i) {
        if(!estDetruit[i]) {
            astres[k++] = astres[i];
        }
    }
    astres.resize(k);

    for(const auto& na : nouveauxAstres) {
        astres.push_back(na);
    }

    for (auto& a : astres) {
        a.position += a.vitesse * dt;
    }
}

astre physique::fusionner(const astre &a, const astre &b) {

    astre nouvelAstre(
        (a.position * a.masse + b.position * b.masse) / (a.masse + b.masse),
        (a.vitesse * a.masse + b.vitesse * b.masse) / (a.masse + b.masse),
        a.masse + b.masse,
        std::cbrt(std::pow(a.forme.getRadius(), 3) + std::pow(b.forme.getRadius(), 3)),
        sf::Color(
            (a.forme.getFillColor().r + b.forme.getFillColor().r) / 2,
            (a.forme.getFillColor().g + b.forme.getFillColor().g) / 2,
            (a.forme.getFillColor().b + b.forme.getFillColor().b) / 2
        )
    );

    return nouvelAstre;
}
