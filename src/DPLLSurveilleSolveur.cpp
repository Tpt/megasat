#include "../include/DPLLSurveilleSolveur.h"
#include<list>

using namespace std;

DPLLSurveilleSolveur::DPLLSurveilleSolveur(Formule &formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_, GestionConflits& gestionConflits_, TheorieGreffon& theorieGreffon_) : AbstractDPLLSolveur(formule_, variableNonAssigneeProvider_, gestionConflits_, theorieGreffon_), literauxSurveilles(unordered_map<int,pair<int,int>>())
{}

bool DPLLSurveilleSolveur::isSatifiable()
{
    try
    {
        AbstractDPLLSolveur::initialisation();
        initialiserLiterauxSurveilles();
        assigneUneVariable();
        return true;
    }
    catch(InsatisfiableException)
    {
        return false;
    }
}

void DPLLSurveilleSolveur::initialiserLiterauxSurveilles()
{
    for(Clause* clause : formule.getClauses())
        initialiseClauseWatchedLiterals(clause);
}

Clause* DPLLSurveilleSolveur::addClause(std::vector<int> clause, int uid)
{
    Clause* clauseObj = AbstractDPLLSolveur::addClause(clause, uid);
    if(clauseObj == nullptr)
        return nullptr;
    initialiseClauseWatchedLiterals(clauseObj);
    return clauseObj;
}

void DPLLSurveilleSolveur::initialiseClauseWatchedLiterals(Clause* clause)
{
    Literal* premierLiteral = trouveLiteralASurveille(clause);
    Literal* secondLiteral = trouveLiteralASurveille(clause, premierLiteral);
    literauxSurveilles[clause->getUid()] = pair<int,int>(premierLiteral->getId(), secondLiteral->getId());
}

Literal* DPLLSurveilleSolveur::trouveLiteralASurveille(Clause* clause, Literal* autreLiteral)
{
    list<Literal*> literauxASupprimer;
    for(Literal* literal : clause->getLiteraux())
        switch(literal->eval())
        {
        case VRAI:
        case INCONNU:
            if(literal != autreLiteral)
            {
                clause->supprimerLiteraux(literauxASupprimer);
                return literal;
            }
            break;
        case FAUX:
            literauxASupprimer.push_front(literal);
        default:
            break;
        }
    clause->supprimerLiteraux(literauxASupprimer);

    if(clause->isVide()) //la simplification à aboutie à une clause vide
        leveExceptionLorsConflit(clause);

    return autreLiteral;
}


void DPLLSurveilleSolveur::assigneLiteral(int literalId)
{
    Variable* var = formule.getVar(abs(literalId));
    var->setVal(literalId > 0);

#ifdef DEBUG
    cout << "c assigne " << var->getId() << " a " << var->getVal() << endl;
#endif

    Literal* literal = formule.getLiteral(literalId);
    onLiteralAssigne(literal);

    TPropagation();
    return assigneUneVariable();
}

void DPLLSurveilleSolveur::onLiteralAssigne(Literal* literal)
{
    int literalId = literal->getId();

    for(Clause* clause : formule.getClauses())
    {
        //si elle contient le litéral assigné à vrai, on la supprime
        if(clause->literalPresent(literal))
        {
            formule.supprimerClause(clause);
            continue;
        }

        //on propage si l'un des litéraux surveillés est -literalId
        pair<int, int> literaux = literauxSurveilles[clause->getUid()];

        if(literaux.first == -literalId)
            assigneLiteralAFauxDansClause(clause, literaux.first, literaux.second);
        else if(literaux.second == -literalId)
            assigneLiteralAFauxDansClause(clause, literaux.second, literaux.first);
    }
}

void DPLLSurveilleSolveur::assigneLiteralAFauxDansClause(Clause* clause, int literalId, int autreLiteralId)
{
    Literal* autreLiteral = formule.getLiteral(autreLiteralId);

    clause->supprimer(formule.getLiteral(literalId)); //on supprime le litéral de la clause

    Literal* nouveauLiteral = trouveLiteralASurveille(clause, autreLiteral);

    if(nouveauLiteral == autreLiteral) //il n'y a qu'un seul litéral qui ne soit pas à faux
    {
        if(nouveauLiteral->isAssigne())
        {
            if(nouveauLiteral->getVal())
            {
                formule.supprimerClause(clause); //la clause est satisfaite
            }
            else //la formule n'est pas satisfiable : tout les litéraux sont à faux
            {
                leveExceptionLorsConflit(clause);
            }
        }
        else
        {
#ifdef DEBUG
            cout << "c pas de choix : " << nouveauLiteral->getId() << " true" << endl; //il n'y a plus qu'un litéral dans la clause : il faut le mettre à vrai
#endif
            onDeduction(nouveauLiteral, clause->getUid());
            nouveauLiteral->setVal(true);
            onLiteralAssigne(nouveauLiteral);
        }
    }
    else
    {
        literauxSurveilles[clause->getUid()] = pair<int,int>(nouveauLiteral->getId(), autreLiteralId);

#ifdef DEBUG
        cout << "c nouveaux literaux " << nouveauLiteral->getId() << ' ' << autreLiteralId << " a la place de " << literalId << ' ' << autreLiteralId << endl;
#endif
    }
}

void DPLLSurveilleSolveur::TPropagation()
{
    if(!gestionConflits.isCompatibleAvecTPropagation())
        return;
    
    vector<int> literauxAAssigner = theorieGreffon.getTPropagations(static_cast<unsigned int>(profondeurPile));
    
    if(literauxAAssigner.empty())
        return;
    
    for(int literalId : literauxAAssigner)
    {
#ifdef DEBUG
        cout << "c deduction de la théorie : " << literalId << " true." << endl;
#endif
        Literal* literal = formule.getLiteral(literalId);
        literal->setVal(true);
        onLiteralAssigne(literal);
    }
}