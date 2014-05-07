#ifndef ATOMECONGRUENCE_H
#define ATOMECONGRUENCE_H

#include "Terme.h"

class AtomeCongruence
{
public:
    AtomeCongruence();
    virtual ~AtomeCongruence();

private:
    Terme gauche;
    Terme droite;
};

#endif // ATOMECONGRUENCE_H
