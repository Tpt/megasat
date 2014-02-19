#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

DPLLSolveur::DPLLSolveur(Formule &formule_, bool avecLiterauxSurveilles_) : Solveur(formule_), avecLiterauxSuerveilles(avecLiterauxSurveilles_)
{}

bool DPLLSolveur::isSatifiable()
{
    
    return true;
}
