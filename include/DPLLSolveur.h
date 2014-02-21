#ifndef DPLLSolveur_H
#define DPLLSolveur_H

#include"Solveur.h"

class DPLLSolveur : public Solveur
{
public:
    DPLLSolveur(Formule &formule, bool avecLiterauxSurveilles = true);
    bool isSatifiable();
private:
    bool avecLiterauxSurveilles;
    bool assigneUneVariableEtRetourneSatisfiabilite();
    bool assigneVariableEtRetourneSatisfiabilite(int varId, bool val);
    bool aClauseVide();
    int getVariableNonAssignee();
};

#endif