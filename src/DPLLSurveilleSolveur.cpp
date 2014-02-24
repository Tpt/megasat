#include<vector>
#include<unordered_set>
#include "../include/DPLLSurveilleSolveur.h"

using namespace std;

DPLLSurveilleSolveur::DPLLSurveilleSolveur(Formule &formule_) : Solveur(formule_), literauxSurveilles(unordered_map<int,pair<int,int>>())
{}

bool DPLLSurveilleSolveur::isSatifiable()
{
    return assigneUneVariableEtRetourneSatisfiabilite();
}

bool DPLLSurveilleSolveur::assigneUneVariableEtRetourneSatisfiabilite()
{
    int varId = 1; //TODO
    if(varId == -1)
        return true;

    Formule save = formule;

    if(assigneVariableEtRetourneSatisfiabilite(varId, true))
        return true;

    //backtrack
    formule = save;
    if(assigneVariableEtRetourneSatisfiabilite(varId, false))
        return true;

    return false;
}

bool DPLLSurveilleSolveur::assigneVariableEtRetourneSatisfiabilite(int varId, bool val)
{
    Variable* var = formule.getVar(varId - 1);
    var->setVal(val);
    std::cout << "assigne " << var->getId() << " a " << var->getVal() << std::endl;

    //TODO simplification

    return assigneUneVariableEtRetourneSatisfiabilite();
}

void DPLLSurveilleSolveur::initialiserLiterauxSurveilles()
{
    for(Clause* clause : formule.getClauses())
    {
        int premierLiteral = trouveLiteralASurveille(clause);
        int secondLiteral = trouveLiteralASurveille(clause, premierLiteral);
        literauxSurveilles[clause->getUid()] = pair<int,int>(premierLiteral, secondLiteral);
    }
}

int DPLLSurveilleSolveur::trouveLiteralASurveille(Clause* clause, int autreLiteral)
{
    for(Literal* literal : clause->getLiteraux())
        if((!literal->isAssignee() || literal->getVar()) && literal->getId() != autreLiteral)
            return literal->getId();
    return autreLiteral;
}

void DPLLSurveilleSolveur::onLiteralAssigne(int literalId)
{
    for(auto& clauseEtLiterauxSurveilles : literauxSurveilles)
    {
        if(clauseEtLiterauxSurveilles.second.first == -literalId)
        {
            Clause* clause = new Clause(0); //TODO
            assigneLiteralAFauxDansClause( clause, -literalId);
            clauseEtLiterauxSurveilles.second.first = trouveLiteralASurveille(clause, clauseEtLiterauxSurveilles.second.second);
        }
        else if(clauseEtLiterauxSurveilles.second.second == -literalId)
        {
            Clause* clause = new Clause(0); //TODO
            assigneLiteralAFauxDansClause( clause, -literalId);
            clauseEtLiterauxSurveilles.second.second = trouveLiteralASurveille(clause, clauseEtLiterauxSurveilles.second.first);
        }
    }
}

void DPLLSurveilleSolveur::assigneLiteralAFauxDansClause(Clause* clause, int literalId)
{
    //TODO
}
