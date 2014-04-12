#ifndef AbstractDPLLSolveur_H
#define AbstractDPLLSolveur_H

#include "Solveur.h"
#include "InsatisfiableException.h"
#include "VariableNonAssigneeProvider.h"
#include "GestionConflits.h"

class AbstractDPLLSolveur : public Solveur
{
public:
    AbstractDPLLSolveur(Formule &formule, VariableNonAssigneeProvider& variableNonAssigneeProvider, GestionConflits& gestionConflits);
    ~AbstractDPLLSolveur();
protected:
    Formule* formuleInitiale;
    VariableNonAssigneeProvider& variableNonAssigneeProvider;
    GestionConflits& gestionConflits;
    void assigneUneVariable();
    virtual void assigneVariable(int varId, bool val) = 0;
};

#endif
