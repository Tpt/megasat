#include "../include/AtomeCongruence.h"

using namespace std;

AtomeCongruence::AtomeCongruence() : gauche(Terme()), droite(Terme())
{}

AtomeCongruence::AtomeCongruence(Terme gauche_, Terme droite_) : gauche(gauche_), droite(droite_)
{}

AtomeCongruence::~AtomeCongruence()
{}

bool AtomeCongruence::isConflit() const
{
    return gauche.isConflit(droite);
}

size_t AtomeCongruence::hash() const
{
    return this->gauche.hash() + this->droite.hash();
}

bool AtomeCongruence::operator==(const AtomeCongruence& that) const
{
    return (this->gauche == that.gauche && this->droite == that.droite) ||
        (this->gauche == that.droite && this->droite == that.gauche);
}