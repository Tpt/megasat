#ifndef AbstractDPLLSolveur_H
#define AbstractDPLLSolveur_H

#include "Solveur.h"
#include "InsatisfiableException.h"
#include "VariableNonAssigneeProvider.h"
#include "GestionConflits.h"

class AbstractDPLLSolveur : public Solveur
{
public:
    AbstractDPLLSolveur(const AbstractDPLLSolveur& other);
    AbstractDPLLSolveur& operator=(const AbstractDPLLSolveur& other);
    AbstractDPLLSolveur(Formule &formule, VariableNonAssigneeProvider& variableNonAssigneeProvider, GestionConflits& gestionConflits);
    ~AbstractDPLLSolveur();
protected:
    Formule* formuleInitiale;
    VariableNonAssigneeProvider& variableNonAssigneeProvider;
    GestionConflits& gestionConflits;
    void assigneUneVariable();
    virtual void assigneLiteral(int literalId) = 0;
};

#endif
