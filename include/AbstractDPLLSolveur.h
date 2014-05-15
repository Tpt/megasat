#ifndef AbstractDPLLSolveur_H
#define AbstractDPLLSolveur_H

#include "Solveur.h"
#include "InsatisfiableException.h"
#include "VariableNonAssigneeProvider.h"
#include "GestionConflits.h"
#include "TheorieGreffon.h"
#include<map>

class AbstractDPLLSolveur : public Solveur
{
public:
    AbstractDPLLSolveur(Formule &formule, VariableNonAssigneeProvider& variableNonAssigneeProvider, GestionConflits& gestionConflits, TheorieGreffon& theorieGreffon);
    ~AbstractDPLLSolveur();
protected:
    VariableNonAssigneeProvider& variableNonAssigneeProvider;
    GestionConflits& gestionConflits;
    TheorieGreffon& theorieGreffon;
    void initialisation();
    void assigneUneVariable();
    virtual void assigneLiteral(int literalId) = 0;
    void onChoix(int literalId);
    void onDeduction(Literal* literal, int clauseUid);
    void onAssignation(int literalId);
    void addClauses(std::map<int,std::vector<int>> clausesToAdd);
    virtual Clause* addClause(std::vector<int> clause, int uid);

    void __attribute__((noreturn)) leveExceptionLorsConflit(Clause* clause);
    int profondeurPile;
};

class InsatisfiableExceptionAvecClauses : public InsatisfiableException
{
public:
    InsatisfiableExceptionAvecClauses(int profondeurBacktrack = 0) noexcept;
    ~InsatisfiableExceptionAvecClauses() noexcept {};
    void addClause(const std::pair<int,std::vector<int>>& clause);
    std::map<int,std::vector<int>> getClauses() const;
    int getProfondeurBacktrack() const __attribute__((pure));
    void decrementeProfondeurBacktrack();
private:
    int profondeurBacktrack;
    std::map<int,std::vector<int>> clausesToAdd;
};

#endif
