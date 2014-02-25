#include<vector>
#include<unordered_set>
#include "../include/AbstractDPLLSolveur.h"

AbstractDPLLSolveur::AbstractDPLLSolveur(Formule &formule_) : Solveur(formule_)
{}

AbstractDPLLSolveur::~AbstractDPLLSolveur()
{}

void AbstractDPLLSolveur::assigneUneVariable()
{
    int varId = getVariableNonAssignee();
    if(varId == -1)
        return;

    Formule save = formule;

    try
    {
        assigneVariable(varId, true);
    }
    catch(InsatisfiableException)
    {
        //backtrack
        formule = save;
        assigneVariable(varId, false);
    }
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
