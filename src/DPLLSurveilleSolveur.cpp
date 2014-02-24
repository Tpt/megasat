#include "../include/DPLLSurveilleSolveur.h"

using namespace std;

DPLLSurveilleSolveur::DPLLSurveilleSolveur(Formule &formule_) : AbstractDPLLSolveur(formule_), literauxSurveilles(unordered_map<int,pair<int,int>>())
{}

bool DPLLSurveilleSolveur::isSatifiable()
{
    formule.supprimerTautologies();
    initialiserLiterauxSurveilles();

    return assigneUneVariableEtRetourneSatisfiabilite();
}

void DPLLSurveilleSolveur::initialiserLiterauxSurveilles()
{
    for(Clause* clause : formule.getClauses())
    {
        int premierLiteral = trouveLiteralASurveille(clause);
        int secondLiteral = trouveLiteralASurveille(clause, premierLiteral);
        literauxSurveilles[clause->getUid()] = pair<int,int>(premierLiteral, secondLiteral);
    }
}

int DPLLSurveilleSolveur::trouveLiteralASurveille(Clause* clause, int autreLiteral)
{
    for(Literal* literal : clause->getLiteraux())
        if((!literal->isAssignee() || literal->getVar()) && literal->getId() != autreLiteral)
            return literal->getId();
    return autreLiteral;
}


bool DPLLSurveilleSolveur::assigneVariableEtRetourneSatisfiabilite(int varId, bool val)
{
    Variable* var = formule.getVar(varId);
    var->setVal(val);
    std::cout << "assigne " << var->getId() << " a " << var->getVal() << std::endl;

    if(!onLiteralAssigne(val ? varId : -varId))
        return false;

    return assigneUneVariableEtRetourneSatisfiabilite();
}

bool DPLLSurveilleSolveur::onLiteralAssigne(int literalId)
{
    for(Clause* clause : formule.getClauses())
    {
        pair<int, int> literaux = literauxSurveilles[clause->getUid()];

        if(literaux.first == literalId)
            formule.supprimerClause(clause); //elle est vérifiée
        else if(literaux.first == -literalId)
            if(!assigneLiteralAFauxDansClauseEtRetourneEtat( clause, literaux.first, literaux.second))
                return false;

        if(literaux.second == literalId)
            formule.supprimerClause(clause);
        else if(literaux.second == -literalId)
            if(!assigneLiteralAFauxDansClauseEtRetourneEtat( clause, literaux.second, literaux.first))
                return false;
    }
    return true;
}

bool DPLLSurveilleSolveur::assigneLiteralAFauxDansClauseEtRetourneEtat(Clause* clause, int literalId, int autreLiteralId)
{
    clause->print();
    cout << "literaux " << literalId << ' ' << autreLiteralId << endl;

    clause->supprimer(formule.getLiteral(literalId)); //on supprime le litéral de la clause

    int nouveauLiteralId = trouveLiteralASurveille(clause, autreLiteralId);

    if(nouveauLiteralId == autreLiteralId) //il n'y a qu'un seul litéral qui ne soit pas à faux
    {
        Literal* literal = formule.getLiteral(nouveauLiteralId);
        if(literal->isAssignee())
            if(literal->getVal())
            {
                formule.supprimerClause(clause); //la clause est satisfaite
                return true;
            }
            else
                return false; //la formule n'est pas satisfiable : tout les litéraux sont à faux
        else
            return assigneVariableEtRetourneSatisfiabilite(literal->getAbsId(), literal->getPolarite()); //pour valider la clause il faut que le dernier litéral inconnu soit à vrai
        
    }

    literauxSurveilles[clause->getUid()] = pair<int,int>(nouveauLiteralId, autreLiteralId);
    cout << "nouveaux literaux " << nouveauLiteralId << ' ' << autreLiteralId << endl;
    return true;
}
