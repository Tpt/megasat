#include<vector>
#include<unordered_set>
#include "../include/DPLLSolveur.h"

using namespace std;

DPLLSolveur::DPLLSolveur(Formule& formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_, GestionConflits& gestionConflits_, TheorieGreffon& theorieGreffon_) :
AbstractDPLLSolveur(formule_, variableNonAssigneeProvider_, gestionConflits_, theorieGreffon_)
{}

DPLLSolveur::~DPLLSolveur()
{}

bool DPLLSolveur::isSatifiable()
{
    try
    {
        AbstractDPLLSolveur::initialisation();
        simplifier();
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
    while(propagationUnitaire() || eliminationLiterauxPurs() || TPropagation())
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
            onDeduction(literal, clause->getUid(), profondeurPile);
            literal->setVal(true);
            return true;
        }
    }
    return false;
}

bool DPLLSolveur::eliminationLiterauxPurs()
{
    if(!theorieGreffon.avecEliminationLiterauxPurs())
        return false;

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

    for(Clause* c : formule.getClauses())
    {
        Polarite res = c->polariteLiteral(id);
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

bool DPLLSolveur::TPropagation()
{
    if(!gestionConflits.isCompatibleAvecTPropagation())
        return false;

    vector<int> literauxAAssigner = theorieGreffon.getTPropagations(static_cast<unsigned int>(profondeurPile));

    if(literauxAAssigner.empty())
        return false;

    for(int literalId : literauxAAssigner)
    {
#ifdef DEBUG
        cout << "c deduction de la théorie : " << literalId << " true." << endl;
#endif

        formule.setVar(literalId, true);
    }

    return true;
}
