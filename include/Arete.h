#ifndef Arete_H
#define Arete_H

#include <cstddef>

class Arete
{
public:
    Arete(int extremiteGauche, int extremiteDroite);

    int getExtremiteGauche() const __attribute__((pure));
    int getExtremiteDroite() const __attribute__((pure));

    bool operator==(const Arete& that) const __attribute__((pure));
    size_t hash() const __attribute__((pure));

private:
    int extremiteGauche;
    int extremiteDroite;
};

struct AreteHash
{
    size_t operator()(const Arete& arete) const
    {
        return arete.hash();
    };
};

#endif
