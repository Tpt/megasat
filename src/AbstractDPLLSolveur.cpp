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
    try
    {
        profondeurPile++;
        onChoix(literalId);
        assigneLiteral(literalId);
    }
    catch(InsatisfiableExceptionAvecClauses& exception)
    {
        profondeurPile--;
        if(exception.getProfondeurBacktrack() > 0)
        {
            exception.decrementeProfondeurBacktrack();
            throw;
        }

        //backtrack
        formule = save;
        addClauses(exception.getClauses());
        onBacktrack();
        try
        {
            profondeurPile++;
            onChoix(-literalId);
            assigneLiteral(-literalId);
        }
        catch(InsatisfiableExceptionAvecClauses& exception2)
        {
            profondeurPile--;
            exception2.decrementeProfondeurBacktrack();
            //propagation des clauses à ajouter
            for(auto clause : exception.getClauses())
                exception2.addClause(clause);
            throw;
        }
    }
}

void AbstractDPLLSolveur::onChoix(int literalId)
{
    gestionConflits.onChoix(literalId, profondeurPile);
    onAssignation(literalId);
}

void AbstractDPLLSolveur::onDeduction(Literal* literal, int clauseUid)
{
    gestionConflits.onDeduction(literal, clauseUid, profondeurPile);
    onAssignation(literal->getId());
}

void AbstractDPLLSolveur::onBacktrack()
{
    gestionConflits.onBacktrack(profondeurPile + 1);
    theorieGreffon.onBacktrack(static_cast<unsigned int>(profondeurPile + 1));
}

void AbstractDPLLSolveur::onAssignation(int literalId)
{
    vector<int> clauseAAjouter = theorieGreffon.onAssignation(literalId, static_cast<unsigned int>(profondeurPile));

    if(clauseAAjouter.size() > 0)
    {
#ifdef DEBUG
        cout << "c backtrack causé par la théorie. Clause ajoutée : ";
        for(int l : clauseAAjouter)
            cout << l << ' ';
        cout << endl;
#endif
        InsatisfiableExceptionAvecClauses exception(0);
        //exception.addClause(pair<int,vector<int>>(Clause::genUid(), clauseAAjouter));
        throw exception;
    }
}

void __attribute__((noreturn)) AbstractDPLLSolveur::leveExceptionLorsConflit(Clause* clause)
{
    auto retour = gestionConflits.onConflit(clause->getUid(), profondeurPile);
    InsatisfiableExceptionAvecClauses exception(retour.first);
    if(retour.second.first >= 0)
        exception.addClause(retour.second);

#ifdef DEBUG
    cout << "c backtrack de " << retour.first + 1 << " niveaux vers le niveau " << profondeurPile - retour.first - 1 << ". Clause ajoutée : ";
    for(int l : retour.second.second)
        cout << l << ' ';
    cout << endl;
#endif
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
