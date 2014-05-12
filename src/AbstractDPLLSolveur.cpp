#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<cstdlib>
#include "../include/AbstractDPLLSolveur.h"

using namespace std;

AbstractDPLLSolveur::AbstractDPLLSolveur(Formule& formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_, GestionConflits& gestionConflits_, TheorieGreffon& theorieGreffon_) :
Solveur(formule_), variableNonAssigneeProvider(variableNonAssigneeProvider_), gestionConflits(gestionConflits_), theorieGreffon(theorieGreffon_), profondeurPile(0)
{}

AbstractDPLLSolveur::~AbstractDPLLSolveur()
{}

void AbstractDPLLSolveur::initialisation()
{
    profondeurPile = 0;
    formule.supprimerTautologies();

    gestionConflits.onBeginning(&formule);
    theorieGreffon.onBeginning(&formule);
}

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
        onChoix(literalId, profondeurPile);
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
        addClauses(exception.getClauses());
        try
        {
            profondeurPile++;
            onChoix(-literalId, profondeurPile);
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

void AbstractDPLLSolveur::onChoix(int literalId, int profondeurPile)
{
    gestionConflits.onChoix(literalId, profondeurPile);
    onAssignation(literalId, profondeurPile);
}

void AbstractDPLLSolveur::onDeduction(Literal* literal, int clauseUid, int profondeurPile)
{
    gestionConflits.onDeduction(literal, clauseUid, profondeurPile);
    onAssignation(literal->getId(), profondeurPile);
}

void AbstractDPLLSolveur::onAssignation(int literalId, int profondeurPile)
{
    vector<int> clauseAAjouter = theorieGreffon.onAssignation(literalId, profondeurPile);
    
    if(clauseAAjouter.size() > 0)
    {
        InsatisfiableExceptionAvecClauses exception(0);
        exception.addClause(pair<int,vector<int>>(Clause::genUid(), clauseAAjouter));
        gestionConflits.onBacktrack(profondeurPile);
        theorieGreffon.onBacktrack(profondeurPile);
        profondeurPile--;
        throw exception;
    }
}

void __attribute__((noreturn)) AbstractDPLLSolveur::leveExceptionLorsConflit(Clause* clause)
{
    auto retour = gestionConflits.onConflit(clause->getUid(), profondeurPile);
    gestionConflits.onBacktrack(profondeurPile);
    theorieGreffon.onBacktrack(profondeurPile);
    profondeurPile--;
    InsatisfiableExceptionAvecClauses exception(retour.first);
    if(retour.second.first >= 0)
        exception.addClause(retour.second);
    throw exception;
}

void AbstractDPLLSolveur::addClauses(std::map<int,std::vector<int>> clausesToAdd)
{
    for(auto clause : clausesToAdd)
    {
        addClause(clause.second, clause.first);
    }
}

Clause* AbstractDPLLSolveur::addClause(std::vector<int> clause, int uid)
{
    gestionConflits.addClause(clause, uid);
    return formule.addClause(clause, uid);
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

int InsatisfiableExceptionAvecClauses::getProfondeurBacktrack() const
{
    return profondeurBacktrack;
}

void InsatisfiableExceptionAvecClauses::decrementeProfondeurBacktrack()
{
    profondeurBacktrack--;
}
