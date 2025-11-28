#ifndef S0L4R_ASTRE_H
#define S0L4R_ASTRE_H

#include <SFML/Graphics.hpp>
#include <deque>

class astre {

    public:
        sf::Vector2f position;
        sf::Vector2f vitesse;
        float rayon;
        float masse;
        sf::CircleShape forme;

        std::deque<sf::Vector2f> trajectoire;
        static constexpr size_t MAX_TRAIL = 2000;

        astre();

        astre(sf::Vector2f pos, sf::Vector2f vit, float m, float rayon, sf::Color couleur);

        void draw(sf::RenderWindow &window);

};


#endif //S0L4R_ASTRE_H