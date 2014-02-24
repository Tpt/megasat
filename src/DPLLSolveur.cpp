#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

DPLLSolveur::DPLLSolveur(Formule &formule_) : AbstractDPLLSolveur(formule_)
{}

DPLLSolveur::~DPLLSolveur()
{}

bool DPLLSolveur::isSatifiable()
{
    formule.supprimerTautologies();
    formule.simplifier();
    if(aClauseVide())
        return false;
    if(formule.isVide())
        return true;

    return assigneUneVariableEtRetourneSatisfiabilite();
}

bool DPLLSolveur::assigneVariableEtRetourneSatisfiabilite(int varId, bool val)
{
    Variable* var = formule.getVar(varId);
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
