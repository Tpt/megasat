#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

using namespace std;

DPLLSolveur::DPLLSolveur(Formule& formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_, GestionConflits& gestionConflits_) :
AbstractDPLLSolveur(formule_, variableNonAssigneeProvider_, gestionConflits_)
{}

DPLLSolveur::~DPLLSolveur()
{}

bool DPLLSolveur::isSatifiable()
{
    profondeurPile = 0;
    gestionConflits.onBeggining(&formule);

    //on fait quelques simplifications préliminaires
    formule.supprimerTautologies();
    simplifier();

    if(formule.isVide())
        return true;

    try
    {
        verifierAPasClauseVide();
        assigneUneVariable();
        return true;
    }
    catch(InsatisfiableException)
    {
        return false;
    }
}

void DPLLSolveur::assigneLiteral(int literalId)
{
    Variable* var = formule.getVar(abs(literalId));
    var->setVal(literalId > 0);
#ifdef DEBUG
    cout << "c assigne " << var->getId() << " a " << var->getVal() << std::endl;
#endif

    simplifier();

    verifierAPasClauseVide();
    if(formule.isVide())
        return;

    assigneUneVariable();
}

void DPLLSolveur::verifierAPasClauseVide()
{
    for(auto clause : formule.getClauses())
    {
        if(clause->isVide())
            leveExceptionLorsConflit(clause);
    }
}

void DPLLSolveur::simplifier() ///Arret mortellement dangereux ! Mais garanti 100% safe (a quelques exceptions près).
{
    compacter();
    while(propagationUnitaire() || eliminationLiterauxPurs())
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

bool DPLLSolveur::propagationUnitaire()
{
    bool modif = false;

    for(Clause* c : formule.getClauses())
    {
        if(simplificationUnitaire(c))
            modif = true;
    }

    return modif;
}

bool DPLLSolveur::simplificationUnitaire(Clause* clause)
{
    if(clause->size() != 1)
        return false;

    for( Literal* literal : clause->getLiteraux())
    {
        if(!literal->isAssigne())
        {
            gestionConflits.onDeduction(literal, clause->getUid(), profondeurPile);
            literal->setVal(true);
            return true;
        }
    }
    return false;
}

bool DPLLSolveur::eliminationLiterauxPurs()
{
    bool modif = false;
    
    for(int id = 1; id <= formule.getNombreDeVariables(); ++id)
        if(simplificationLiteralPur(id))
            modif = true;
    
    return modif;
}

bool DPLLSolveur::simplificationLiteralPur(int id)
{
    bool found_pos = false;
    bool found_neg = false;
    Polarite res;

    for(Clause* c : formule.getClauses())
    {
        res = c->polariteLiteral(id);
        if(res == POSITIF)
            found_pos = true;
        else if(res == NEGATIF)
            found_neg = true;
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
