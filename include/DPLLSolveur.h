#ifndef DPLLSolveur_H
#define DPLLSolveur_H

#include"Solveur.h"

class DPLLSolveur : public Solveur
{
public:
    DPLLSolveur(Formule &formule);
    ~DPLLSolveur();
    bool isSatifiable();
private:
    bool assigneUneVariableEtRetourneSatisfiabilite();
    bool assigneVariableEtRetourneSatisfiabilite(int varId, bool val);
    bool aClauseVide();
    int getVariableNonAssignee();
};

#endif
