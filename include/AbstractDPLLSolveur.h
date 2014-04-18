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
    void leveExceptionLorsConflit [[noreturn]] (Clause* clause);
    int profondeurPile;
};

class InsatisfiableExceptionAvecClauses : public InsatisfiableException
{
public:
    InsatisfiableExceptionAvecClauses(int profondeurBacktrack = 0) noexcept;
    ~InsatisfiableExceptionAvecClauses() noexcept {};
    void addClause(const std::pair<int,std::vector<int>>& clause);
    std::map<int,std::vector<int>> getClauses() const;
    void addClausesToFormule(Formule& formule) const;
    int getProfondeurBacktrack() const __attribute__((pure));
    void decrementeProfondeurBacktrack();
private:
    int profondeurBacktrack;
    std::map<int,std::vector<int>> clausesToAdd;
};

#endif
