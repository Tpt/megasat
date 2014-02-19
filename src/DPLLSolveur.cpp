#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

DPLLSolveur::DPLLSolveur(Formule &formule_) : Solveur(formule_)
{}

bool DPLLSolveur::isSatifiable()
{
    return true;
}
