#ifndef AbstractDPLLSolveur_H
#define AbstractDPLLSolveur_H

#include "Solveur.h"
#include "InsatisfiableException.h"
#include "VariableNonAssigneeProvider.h"

class AbstractDPLLSolveur : public Solveur
{
public:
    AbstractDPLLSolveur(Formule &formule, VariableNonAssigneeProvider& variableNonAssigneeProvider);
    ~AbstractDPLLSolveur();
protected:
    VariableNonAssigneeProvider& variableNonAssigneeProvider;
    void assigneUneVariable();
    virtual void assigneVariable(int varId, bool val) = 0;
};

#endif
