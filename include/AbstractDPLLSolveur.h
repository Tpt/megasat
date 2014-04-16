#ifndef AbstractDPLLSolveur_H
#define AbstractDPLLSolveur_H

#include "Solveur.h"
#include "InsatisfiableException.h"
#include "VariableNonAssigneeProvider.h"
#include "GestionConflits.h"
#include<map>

class AbstractDPLLSolveur : public Solveur
{
public:
    AbstractDPLLSolveur(Formule &formule, VariableNonAssigneeProvider& variableNonAssigneeProvider, GestionConflits& gestionConflits);
    ~AbstractDPLLSolveur();
protected:
    VariableNonAssigneeProvider& variableNonAssigneeProvider;
    GestionConflits& gestionConflits;
    void assigneUneVariable();
    virtual void assigneLiteral(int literalId) = 0;
};

class InsatisfiableExceptionAvecClauses : public InsatisfiableException
{
public:
    void addClause(const std::pair<int,std::vector<int>>& clause);
    std::map<int,std::vector<int>> getClauses() const;
    void addClausesToFormule(Formule& formule) const;
private:
    std::map<int,std::vector<int>> clausesToAdd;
};

#endif
