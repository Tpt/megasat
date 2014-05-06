#include "../include/Arete.h"

Arete::Arete(int extremiteGauche_, int extremiteDroite_) : extremiteGauche(extremiteGauche_), extremiteDroite(extremiteDroite_)
{}

int Arete::getExtremiteGauche() const
{
    return extremiteGauche;
}

int Arete::getExtremiteDroite() const
{
    return extremiteDroite;
}

bool Arete::operator==(const Arete& that) const
{
    return (extremiteGauche == that.extremiteGauche && extremiteDroite == that.extremiteDroite) ||
        (extremiteGauche == that.extremiteDroite && extremiteDroite == that.extremiteGauche);
}

size_t Arete::hash() const {
    std::hash<int> hasher;
    return hasher(extremiteGauche) + hasher(extremiteDroite);
}
