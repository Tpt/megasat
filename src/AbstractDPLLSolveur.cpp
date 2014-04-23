#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<cstdlib>
#include "../include/AbstractDPLLSolveur.h"

using namespace std;

AbstractDPLLSolveur::AbstractDPLLSolveur(Formule& formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_, GestionConflits& gestionConflits_) :
Solveur(formule_), variableNonAssigneeProvider(variableNonAssigneeProvider_), gestionConflits(gestionConflits_), profondeurPile(0)
{}

AbstractDPLLSolveur::~AbstractDPLLSolveur()
{}

void AbstractDPLLSolveur::assigneUneVariable()
{
    int literalId;
    try
    {
        literalId = variableNonAssigneeProvider.getVariableNonAssignee(formule);
    }
    catch(PlusDeVariablesAAssigner)
    {
        return;
    }

    Formule save = formule;
    profondeurPile++;
    try
    {
        gestionConflits.onChoix(literalId, profondeurPile);
        assigneLiteral(literalId);
    }
    catch(InsatisfiableExceptionAvecClauses& exception)
    {
        if(exception.getProfondeurBacktrack() > 0)
        {
            exception.decrementeProfondeurBacktrack();
            profondeurPile--;
            throw;
        }

        //backtrack
        formule = save;
        exception.addClausesToFormule(formule);
        try
        {
            profondeurPile++;
            gestionConflits.onChoix(-literalId, profondeurPile);
            assigneLiteral(-literalId);
        }
        catch(InsatisfiableExceptionAvecClauses& exception2)
        {
            //propagation des clauses à ajouter
            for(auto clause : exception.getClauses())
                exception2.addClause(clause);
            exception2.decrementeProfondeurBacktrack();
            profondeurPile--;
            throw;
        }
    }
}

void __attribute__((noreturn)) AbstractDPLLSolveur::leveExceptionLorsConflit(Clause* clause)
{
    auto retour = gestionConflits.onConflit(clause->getUid(), profondeurPile);
    profondeurPile--;
    InsatisfiableExceptionAvecClauses exception(retour.first);
    if(retour.second.first >= 0)
        exception.addClause(retour.second);
    throw exception;
}


InsatisfiableExceptionAvecClauses::InsatisfiableExceptionAvecClauses(int profondeurBacktrack_) noexcept :
profondeurBacktrack(profondeurBacktrack_), clausesToAdd(map<int,vector<int>>())
{}

void InsatisfiableExceptionAvecClauses::addClause(const pair<int,vector<int>>& clause)
{
    clausesToAdd[clause.first] = clause.second;
}

std::map<int,std::vector<int>> InsatisfiableExceptionAvecClauses::getClauses() const
{
    return clausesToAdd;
}

void InsatisfiableExceptionAvecClauses::addClausesToFormule(Formule& formule) const
{
    for(auto clause : clausesToAdd)
    {
        formule.addClause(clause.second, clause.first);
    }
}

int InsatisfiableExceptionAvecClauses::getProfondeurBacktrack() const
{
    return profondeurBacktrack;
}

void InsatisfiableExceptionAvecClauses::decrementeProfondeurBacktrack()
{
    profondeurBacktrack--;
}
