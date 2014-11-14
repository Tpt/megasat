#include "../include/Solveur.h"

Solveur::Solveur(Formule& formule_) : formule(formule_)
{}

Solveur::~Solveur()
{}

Formule Solveur::getFomule() const
{
    return formule;
}
