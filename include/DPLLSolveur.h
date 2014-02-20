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
    bool assigneVariableEtRetourneSatisfiabilite(Variable* var, bool val);
    bool aClauseVide();
    Variable* getVariableNonAssignee();
};

#endif