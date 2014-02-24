#include<vector>
#include<unordered_set>
#include "../include/AbstractDPLLSolveur.h"

AbstractDPLLSolveur::AbstractDPLLSolveur(Formule &formule_) : Solveur(formule_)
{}

AbstractDPLLSolveur::~AbstractDPLLSolveur()
{}

bool AbstractDPLLSolveur::assigneUneVariableEtRetourneSatisfiabilite()
{
    int varId = getVariableNonAssignee();
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

int AbstractDPLLSolveur::getVariableNonAssignee()
{
    for(Variable* var : formule.getVars())
    {
        if(!var->isAssignee())
            return var->getId();
    }
    return -1;
}
