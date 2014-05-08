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

private:
    Terme gauche;
    Terme droite;
};

#endif // ATOMECONGRUENCE_H
