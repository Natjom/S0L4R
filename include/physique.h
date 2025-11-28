#ifndef S0L4R_PHYSIQUE_H
#define S0L4R_PHYSIQUE_H

#include "astre.h"
#include <vector>
#include <cmath>

class physique {
    public:
        static constexpr float G = 1.f;

        static void appliquerGravite(std::vector<astre>& astres, float dt);

        static astre fusionner(const astre& a, const astre& b);

};


#endif //S0L4R_PHYSIQUE_H