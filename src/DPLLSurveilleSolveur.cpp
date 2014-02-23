#include<vector>
#include<unordered_set>
#include "../include/DPLLSurveilleSolveur.h"

DPLLSurveilleSolveur::DPLLSurveilleSolveur(Formule &formule_) : Solveur(formule_)
{}

bool DPLLSurveilleSolveur::isSatifiable()
{
    return true; //TODO
}