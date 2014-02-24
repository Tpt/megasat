#ifndef AbstractDPLLSolveur_H
#define AbstractDPLLSolveur_H

#include<unordered_map>
#include"Solveur.h"

class AbstractDPLLSolveur : public Solveur
{
public:
    AbstractDPLLSolveur(Formule &formule);
    ~AbstractDPLLSolveur();
protected:
    bool assigneUneVariableEtRetourneSatisfiabilite();
    virtual bool assigneVariableEtRetourneSatisfiabilite(int varId, bool val) = 0;
    int getVariableNonAssignee();
};

#endif