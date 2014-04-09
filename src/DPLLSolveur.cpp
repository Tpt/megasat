#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

using namespace std;

DPLLSolveur::DPLLSolveur(Formule& formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_) : AbstractDPLLSolveur(formule_, variableNonAssigneeProvider_)
{}

DPLLSolveur::~DPLLSolveur()
{}

bool DPLLSolveur::isSatifiable()
{
    //on fait quelques simplifications préliminaires
    formule.supprimerTautologies();
    simplifier();
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
    cout << "c assigne " << var->getId() << " a " << var->getVal() << std::endl;
#endif

    simplifier();

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

void DPLLSolveur::simplifier() ///Arret mortellement dangereux ! Mais garanti 100% safe (a quelques exceptions près).
{
    compacter();
    while(eliminationLiterauxPurs() || propagationUnitaire())
        compacter();
}

void DPLLSolveur::compacter()
{
    vector<Clause*> clausesASupprimer;
    for(Clause* c : formule.getClauses())
    {
        c->supprimerLiterauxFaux();
        if(c->contientLiteralVrai())
            clausesASupprimer.push_back(c); //on ne peut supprimer directement car cela invaliderait l'itérateur
    }

    for(Clause* c : clausesASupprimer)
        formule.supprimerClause(c);
}

bool DPLLSolveur::eliminationLiterauxPurs()
{
    bool modif=false;

    for(int id=1; id < formule.getNombreDeVariables()+1; ++id)
        if(simplificationLiteralPur(id))
            modif=true;

    return modif;
}

bool DPLLSolveur::propagationUnitaire()
{
    bool modif=false;

    for(Clause* c : formule.getClauses())
    {
        if(c->simplificationUnitaire())
            modif=true;
    }

    if(modif)
        propagationUnitaire();

    return modif;
}

bool DPLLSolveur::simplificationLiteralPur(int id)
{
    bool found_pos=false;
    bool found_neg=false;
    Polarite res;

    for(Clause* c : formule.getClauses())
    {
        res=c->polariteLiteral(id);
        if(res==POSITIF)
            found_pos=true;
        else if(res==NEGATIF)
            found_neg=true;
    }

    if(!found_neg && found_pos)
    {
        formule.getLiteral(id)->setVal(true);
        return true;
    }
    else if(found_neg && !found_pos)
    {
        formule.getLiteral(-id)->setVal(true);
        return true;
    }

    return false;
}
