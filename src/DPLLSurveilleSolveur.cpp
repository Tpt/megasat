#include "../include/DPLLSurveilleSolveur.h"
#include<list>

using namespace std;

DPLLSurveilleSolveur::DPLLSurveilleSolveur(Formule &formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_) : AbstractDPLLSolveur(formule_, variableNonAssigneeProvider), literauxSurveilles(unordered_map<int,pair<int,int>>())
{}

bool DPLLSurveilleSolveur::isSatifiable()
{
    formule.supprimerTautologies();

    try
    {
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
    unordered_set<Clause*> clauses = formule.getClauses();
    for(Clause* clause : clauses)
    {
        Literal* premierLiteral = trouveLiteralASurveille(clause);
        Literal* secondLiteral = trouveLiteralASurveille(clause, premierLiteral);
        literauxSurveilles[clause->getUid()] = pair<int,int>(premierLiteral->getId(), secondLiteral->getId());
    }
}

Literal* DPLLSurveilleSolveur::trouveLiteralASurveille(Clause* clause, Literal* autreLiteral)
{
    list<Literal*> literauxASupprimer;
    unordered_set<Literal*> literaux = clause->getLiteraux();
    for(Literal* literal : literaux)
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
            break;
        default:
            break;
        }
    clause->supprimerLiteraux(literauxASupprimer);

    if(clause->isVide()) //la simplification à aboutie à une clause vide
        throw InsatisfiableException();

    return autreLiteral;
}


void DPLLSurveilleSolveur::assigneVariable(int varId, bool val)
{
    Variable* var = formule.getVar(varId);
    var->setVal(val);

#ifdef DEBUG
    cout << "c assigne " << var->getId() << " a " << var->getVal() << endl;
#endif

    Literal* literal = formule.getLiteral(val ? varId : -varId);
    onLiteralAssigne(literal);

    return assigneUneVariable();
}

void DPLLSurveilleSolveur::onLiteralAssigne(Literal* literal)
{
    int literalId = literal->getId();

    unordered_set<Clause*> clauses = formule.getClauses();
    for(Clause* clause : clauses)
    {
        //si elle contient le litéral assigné à vrai, on a supprime
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
            else
            {
                throw InsatisfiableException(); //la formule n'est pas satisfiable : tout les litéraux sont à faux
            }
        }
        else
        {
#ifdef DEBUG
            cout << "c pas de choix : " << nouveauLiteral->getId() << " true" << endl; //il n'y a plus qu'un litéral dans la clause : il faut le mettre à vrai
#endif

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
