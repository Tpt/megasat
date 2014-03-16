#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

DPLLSolveur::DPLLSolveur(Formule& formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_) : AbstractDPLLSolveur(formule_, variableNonAssigneeProvider_)
{}

DPLLSolveur::~DPLLSolveur()
{}

bool DPLLSolveur::isSatifiable()
{
    //on fait quelques simplifications préliminaires
    formule.supprimerTautologies();
    formule.simplifier();
    if(aClauseVide())
        return false;
    if(formule.isVide())
        return true;

    try
    {
        assigneUneVariable();
        return true;
    }
    catch(InsatisfiableException)
    {
        return false;
    }
}

void DPLLSolveur::assigneVariable(int varId, bool val)
{
    Variable* var = formule.getVar(varId);
    var->setVal(val);
#ifdef DEBUG
    std::cout << "c assigne " << var->getId() << " a " << var->getVal() << std::endl;
#endif

    formule.simplifier();

    if(aClauseVide())
        throw InsatisfiableException();
    if(formule.isVide())
        return;

    assigneUneVariable();
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
