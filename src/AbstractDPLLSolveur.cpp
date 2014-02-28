#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<cstdlib>
#include "../include/AbstractDPLLSolveur.h"

using namespace std;

AbstractDPLLSolveur::AbstractDPLLSolveur(Formule &formule_) : Solveur(formule_)
{}

AbstractDPLLSolveur::~AbstractDPLLSolveur()
{}

void AbstractDPLLSolveur::assigneUneVariable()
{
    pair<int, bool> varIdEtValeurAAssigner = getVariableNonAssignee();
    int varId=varIdEtValeurAAssigner.first;
    bool val=varIdEtValeurAAssigner.second;
    if(varId == -1)
        return;

    Formule save = formule;

    try
    {
        assigneVariable(varId, val);
    }
    catch(InsatisfiableException)
    {
        //backtrack
        formule = save;
        assigneVariable(varId, !val);
    }
}

pair<int, bool> AbstractDPLLSolveur::getVariableNonAssignee() const
{
    for(Variable* var : formule.getVars())
    {
        if(!var->isAssignee())
            return pair<int, bool>(var->getId(),true);
    }
    return pair<int, bool>(-1,true);
}

pair<int, bool> AbstractDPLLSolveur::getVariableNonAssigneeRand() const
{
    vector<int> variablesPossibles(0);

    for(Variable* var : formule.getVars())
        if(!var->isAssignee())
            variablesPossibles.push_back(var->getId());

    return pair<int, bool>(variablesPossibles[rand()%variablesPossibles.size()],true);
}

pair<int, bool> AbstractDPLLSolveur::getVariableNonAssigneeRandMalin() const
{
    vector<int> variablesPossibles(0);

    for(Variable* var : formule.getVars())
        if(!var->isAssignee())
            variablesPossibles.push_back(var->getId());

    int differenceOccurences = 0;
    int varId = variablesPossibles[rand() % variablesPossibles.size()];

    for(Clause* c : formule.getClauses())
        if(c->eval()==INCONNU)
            for(Literal* l : c->getLiteraux())
                if(l->getAbsId()==varId && !l->isAssigne())
                    differenceOccurences += (l->getPolarite() ? 1 : -1);


    return pair<int, bool>(varId,differenceOccurences>=0);
}

pair<int, bool> AbstractDPLLSolveur::getVariableNonAssigneeRandMOMS() const
{
    int tailleMin = -1;

    for(Clause* c : formule.getClauses())
        if(tailleMin == -1 || tailleMin>c->size())
            tailleMin = c->size();

    unordered_map<int, int> occurences;

    for(Clause* c : formule.getClauses())
        if(c->size() == tailleMin && c->eval()==INCONNU)
            for(Literal* l : c->getLiteraux())
                if(!l->isAssigne())
                    occurences[l->getId()]++;

    int literalDOccurenceMaximale=0;

    for(auto occ : occurences)
        if(occ.second > occurences[literalDOccurenceMaximale])
            literalDOccurenceMaximale = occ.first;

    return pair<int, bool>(abs(literalDOccurenceMaximale), occurences[literalDOccurenceMaximale]>0);
}

pair<int, bool> AbstractDPLLSolveur::getVariableNonAssigneeRandDLIS() const
{
    unordered_map<int, int> nombreDeClausesSatisfaitesParLiteral;

    for(Clause* c : formule.getClauses())
        if(c->eval()==INCONNU)
            for(Literal* l : c->getLiteraux())
                if(!l->isAssigne())
                    nombreDeClausesSatisfaitesParLiteral[l->getId()]++;


    int literalDOccurenceMaximale=0;

    for(auto occ : nombreDeClausesSatisfaitesParLiteral)
        if(occ.second > nombreDeClausesSatisfaitesParLiteral[literalDOccurenceMaximale])
            literalDOccurenceMaximale = occ.first;

    return pair<int, bool>(abs(literalDOccurenceMaximale), nombreDeClausesSatisfaitesParLiteral[literalDOccurenceMaximale]>0);

}
