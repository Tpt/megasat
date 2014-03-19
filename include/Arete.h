#ifndef Arete_H
#define Arete_H

#include <cstddef>

class Arete
{
public:
    Arete(int extremiteGauche, int extremiteDroite);

    int getExtremiteGauche() const;
    int getExtremiteDroite() const;

    bool operator==(Arete that) const;
    size_t hash() const;

private:
    int extremiteGauche;
    int extremiteDroite;
};

struct AreteHash {
    size_t operator()(const Arete arete) const {
        return arete.hash();
    };
};

#endif