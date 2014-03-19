#include "../include/VariableNonAssigneeProvider.h"
#include<unordered_map>
#include<climits>
#include "../include/InsatisfiableException.h"

using namespace std;

pair<int, bool> VariableNonAssigneeProviderSimple::getVariableNonAssignee(const Formule& formule) const
{
    for(Variable* var : formule.getVars())
    {
        if(!var->isAssignee())
            return pair<int, bool>(var->getId(), true);
    }
    throw PlusDeVariablesAAssigner();
}

pair<int, bool> VariableNonAssigneeProviderRand::getVariableNonAssignee(const Formule& formule) const
{
    vector<int> variablesPossibles;

    for(Variable* var : formule.getVars())
        if(!var->isAssignee())
            variablesPossibles.push_back(var->getId());

    if(variablesPossibles.empty())
        throw PlusDeVariablesAAssigner();

    return pair<int, bool>(variablesPossibles[rand() % variablesPossibles.size()], true);
}

pair<int, bool> VariableNonAssigneeProviderMalin::getVariableNonAssignee(const Formule& formule) const
{
    vector<int> variablesPossibles;

    for(Variable* var : formule.getVars())
        if(!var->isAssignee())
            variablesPossibles.push_back(var->getId());

    if(variablesPossibles.empty())
        throw PlusDeVariablesAAssigner();

    int differenceOccurences = 0;
    int varId = variablesPossibles[rand() % variablesPossibles.size()];

    for(Clause* c : formule.getClauses())
        if(c->eval() == INCONNU)
            for(Literal* l : c->getLiteraux())
                if(l->getAbsId() == varId && !l->isAssigne())
                    differenceOccurences += (l->getPolarite() ? 1 : -1);


    return pair<int, bool>(varId, differenceOccurences >= 0);
}

pair<int, bool> VariableNonAssigneeProviderMOMS::getVariableNonAssignee(const Formule& formule) const
{
    int tailleMin = INT_MAX;

    for(Clause* c : formule.getClauses())
        if(tailleMin > c->size())
            tailleMin = c->size();

    unordered_map<int, int> occurences;

    for(Clause* c : formule.getClauses())
        if(c->size() == tailleMin && c->eval() == INCONNU)
            for(Literal* l : c->getLiteraux())
                if(!l->isAssigne())
                    occurences[l->getId()]++;

    int literalDOccurenceMaximale = 0;
    for(auto occ : occurences)
        if(occ.second > occurences[literalDOccurenceMaximale])
            literalDOccurenceMaximale = occ.first;

    if(literalDOccurenceMaximale == 0)
        throw PlusDeVariablesAAssigner();

    return pair<int, bool>(abs(literalDOccurenceMaximale), literalDOccurenceMaximale > 0);
}

pair<int, bool> VariableNonAssigneeProviderDLIS::getVariableNonAssignee(const Formule& formule) const
{
    unordered_map<int, int> nombreDeClausesSatisfaitesParLiteral;

    for(Clause* c : formule.getClauses())
        if(c->eval() == INCONNU)
            for(Literal* l : c->getLiteraux())
                if(!l->isAssigne())
                    nombreDeClausesSatisfaitesParLiteral[l->getId()]++;


    int literalDOccurenceMaximale = 0;

    for(auto occ : nombreDeClausesSatisfaitesParLiteral)
        if(occ.second > nombreDeClausesSatisfaitesParLiteral[literalDOccurenceMaximale])
            literalDOccurenceMaximale = occ.first;

    if(literalDOccurenceMaximale == 0)
         throw PlusDeVariablesAAssigner();

    return pair<int, bool>(abs(literalDOccurenceMaximale), nombreDeClausesSatisfaitesParLiteral[literalDOccurenceMaximale] > 0);
}