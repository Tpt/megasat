#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

DPLLSolveur::DPLLSolveur(Formule &formule_, bool avecLiterauxSurveilles_) : Solveur(formule_), avecLiterauxSurveilles(avecLiterauxSurveilles_)
{}

bool DPLLSolveur::isSatifiable()
{
    formule.simplifier();
    if(aClauseVide())
        return false;
    if(formule.isVide())
        return true;

    return assigneUneVariableEtRetourneSatisfiabilite();
}

bool DPLLSolveur::assigneUneVariableEtRetourneSatisfiabilite()
{
    int varId = getVariableNonAssignee();
    if(varId == -1)
        return true; //TODO: on a fini???

    Formule save = formule;

    if(assigneVariableEtRetourneSatisfiabilite(varId, true))
        return true;

    //backtrack
    formule = save;
    if(assigneVariableEtRetourneSatisfiabilite(varId, false))
        return true;

    return false;
}

bool DPLLSolveur::assigneVariableEtRetourneSatisfiabilite(int varId, bool val)
{
    Variable* var = formule.getVar(varId - 1);
    var->setVal(val);
    std::cout << "assigne " << var->getId() << " a " << var->getVal() << std::endl;

    formule.simplifier();

    //TODO: remove
    std::cout << "etat :" << std::endl;
    formule.print();

    if(aClauseVide())
        return false;
    if(formule.isVide())
        return true;

    return assigneUneVariableEtRetourneSatisfiabilite();
}

bool DPLLSolveur::aClauseVide()
{
    for(auto clause : formule.getClauses())
    {
        if(clause->isVide())
            return true;
    }
    return false;
}

int DPLLSolveur::getVariableNonAssignee()
{
    for(Variable* var : formule.getVars())
    {
        if(!var->isAssignee())
            return var->getId();
    }
    return -1;
}