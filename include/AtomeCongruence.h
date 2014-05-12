#ifndef ATOMECONGRUENCE_H
#define ATOMECONGRUENCE_H

#include "Terme.h"

class AtomeCongruence
{
public:
    AtomeCongruence();
    AtomeCongruence(Terme g, Terme d);
    virtual ~AtomeCongruence();
    Terme getGauche() const {return gauche;};
    Terme getDroite() const {return droite;};
    bool isConflit() const;
    size_t hash() const;
    bool operator==(const AtomeCongruence& that) const;

private:
    Terme gauche;
    Terme droite;
};

namespace std
{
    template<> struct hash<AtomeCongruence>
    {
        size_t operator()(const AtomeCongruence& atome) const
        {
            return atome.hash();
        }
    };
}

#endif // ATOMECONGRUENCE_H
