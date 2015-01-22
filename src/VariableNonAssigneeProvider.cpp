#include "../include/VariableNonAssigneeProvider.h"
#include<map>
#include<climits>
#include<ctime>
#include "../include/InsatisfiableException.h"
#include "../include/Rationnel.h"

using namespace std;

int VariableNonAssigneeProviderSimple::getVariableNonAssignee(const Formule& formule) const
{
    for(Variable* var : formule.getVars())
    {
        if(!var->isAssignee())
            return var->getId();
    }
    throw PlusDeVariablesAAssigner();
}

VariableNonAssigneeProviderRand::VariableNonAssigneeProviderRand()
{
    srand(static_cast<unsigned int>(time(NULL)));
}

int VariableNonAssigneeProviderRand::getVariableNonAssignee(const Formule& formule) const
{
    vector<int> variablesPossibles;

    for(Variable* var : formule.getVars())
        if(!var->isAssignee())
            variablesPossibles.push_back(var->getId());

    if(variablesPossibles.empty())
        throw PlusDeVariablesAAssigner();

    return variablesPossibles[static_cast<unsigned long>(rand()) % variablesPossibles.size()];
}

int VariableNonAssigneeProviderMalin::getVariableNonAssignee(const Formule& formule) const
{
    int varId = VariableNonAssigneeProviderRand::getVariableNonAssignee(formule);

    int differenceOccurences = 0;
    for(Clause* c : formule.getClauses())
        if(c->eval() == INCONNU)
            for(Literal* l : c->getLiteraux())
                if(l->getAbsId() == varId && !l->isAssigne())
                    differenceOccurences += (l->getPolarite() ? 1 : -1);


    return (differenceOccurences >= 0) ? varId : -varId;
}

int VariableNonAssigneeProviderMOMS::getVariableNonAssignee(const Formule& formule) const
{
    size_t tailleMin = ULONG_MAX;

    for(Clause* c : formule.getClauses())
        if(tailleMin > c->size())
            tailleMin = c->size();

    map<int, int> occurences;

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

    return literalDOccurenceMaximale;
}

int VariableNonAssigneeProviderDLIS::getVariableNonAssignee(const Formule& formule) const
{
    map<int, int> nombreDeClausesSatisfaitesParLiteral;

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

    return literalDOccurenceMaximale;
}

int VariableNonAssigneeProviderDLISVariante::getVariableNonAssignee(const Formule& formule) const
{
    map<int, Rationnel> scores;

    for(Clause* c : formule.getClauses())
        for(Literal* l : c->getLiteraux())
            scores[l->getId()]+=(Rationnel(1,2).power(c->size()));

    int argmax = 1;
    Rationnel sup = scores[1];

    for(pair<int, Rationnel> score : scores)
    {
        if(sup < score.second)
        {
            argmax = score.first;
            sup = score.second;
        }
    }

    return argmax;
}
