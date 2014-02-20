#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

DPLLSolveur::DPLLSolveur(Formule &formule_, bool avecLiterauxSurveilles_) : Solveur(formule_), avecLiterauxSurveilles(avecLiterauxSurveilles_)
{}

bool DPLLSolveur::isSatifiable()
{
    if(formule.isVide())
        return true;
    return assigneUneVariableEtRetourneSatisfiabilite();
}

bool DPLLSolveur::assigneUneVariableEtRetourneSatisfiabilite()
{
    Variable* var = getVariableNonAssignee();
    if(var == nullptr)
        return true; //TODO: on a fini???

    Formule save(formule);

    if(assigneVariableEtRetourneSatisfiabilite(var, true))
        return true;
    formule = save;
    if(assigneVariableEtRetourneSatisfiabilite(var, false))
        return true;

    return false;
}

bool DPLLSolveur::assigneVariableEtRetourneSatisfiabilite(Variable* var, bool val)
{
    var->setVal(val);
    formule.simplifier();
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

Variable* DPLLSolveur::getVariableNonAssignee()
{
    int nombreDeVariables = formule.getNombreDeVariables();
    for(int i = 0; i < nombreDeVariables; i++)
    {
        Variable* var = formule.getVar(i);
        if(!var->isAssignee())
            return var;
    }
    return nullptr;
}