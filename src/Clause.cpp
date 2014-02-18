#include "../include/Clause.h"
#include<algorithm>
#include<iostream>

using namespace std;

Clause::Clause(int variableNumber) : literaux(unordered_set<Literal*>()), variableNumber(variableNumber)
{}

void Clause::print() const ///Pour le debugage
{
    for(Literal* c : literaux)
    {
        c->print();
        cout << " ";
    }
    cout << endl;
}

void Clause::addLiteral(Literal* l)
{
    literaux.insert(l);
}

void Clause::supprimer(Literal* l) ///Supprime toutes les occurences d'un litéral.
{
    literaux.erase(l);
}

unordered_set<Literal*> Clause::getLiteraux() const
{
    return literaux;
}

int Clause::polariteLiteral(Literal* l1, Literal* l2) const ///Utile pour distinguer les deux parties pour les mariages.
{
    if(literaux.count(l1) != 0)
        return 1;
    else if(literaux.count(l2) != 0)
        return -1;
    else
        return 0;
}

void Clause::fusionner(Clause* c) /** Fusionne la clause avec une autre.
L'utilisation des pointeurs sur les literaux assure (grace à la méthode insert) qu'il n'y a pas de doublons.
**/
{
    unordered_set<Literal*> lit(c->getLiteraux());

    for(Literal* l : lit)
        literaux.insert(l);
}

bool Clause::isTautologie() const ///Test simplement si un literal apparait avec les deux polarités.
{
    vector<bool> foundPos(variableNumber, false);
    vector<bool> foundNeg(variableNumber, false);

    for(Literal* l : literaux)
    {
        if(l->getId()>0)
            foundPos[l->getId()-1]=true;
        else
            foundNeg[-l->getId()-1]=true;
    }

    for(int i=0; i < variableNumber; ++i)
        if(foundNeg[i] && foundPos[i])
            return true;

    return false;
}

void Clause::literalPresent(int id, bool& found_pos, bool& found_neg) const /**Test la présence d'une variable et de sa négation.
On obtient le retour grace aux références en argument. On obtient ainsi la polarite.
**/
{
    for(Literal* l : literaux)
    {
        if(l->getPolarite() && l->getId()==id)
            found_pos = true;
        else if(l->getId() == id)
            found_neg = true;
    }
}

void Clause::literauxPresents(vector<bool>& foundPos, vector<bool>& foundNeg) const /** Idem que précédemment mais avec
toutes les variables
**/
{
    for(Literal* l : literaux)
    {
        if(l->getPolarite())
            foundPos[l->getId()-1];
        else
            foundNeg[-l->getId()-1];
    }
}

int Clause::indiceMax() const ///Donne l'indice maximum des variables de la clause (pour ranger dans les seaux).
{
    int sup = 0;

    for(Literal* l : literaux)
        if(*l > sup)
            sup = l->getAbsId();

    return sup;
}

int Clause::eval() const /**Evalue une clause
Renvoie 0 si la clause est fausse.
1 si la clause est vraie.
2 si une variable n'est pas encore initialisée.
NB : 1 peut être renvoyé alors que certaines variables ne sont pas encore définies.
**/
{
    for(Literal* l : literaux)
    {
        if(!l->isAssigned())
            return 2;
        else if(l->getVal())
            return 1;
    }
    return 0;
}

bool Clause::estSurclause(const Clause* c) const ///Test si la clause est une surclause de la clause donnée en argument.
{
    unordered_set<Literal*> lit(c->getLiteraux());

    for(Literal* l : literaux)
        lit.erase(l);

    return lit.size() == 0;
}

bool Clause::simplificationUnitaire() const
{
    if(size() != 1)
        return false;

    for(Literal* l : literaux) // A refaire !!!!!
        l->setVal(true);

    return true;
}

int Clause::size() const
{
    return static_cast<int>(literaux.size());
}

int Clause::getV() const ///@depreciated
{
    return getVariableNumber();
}

int Clause::getVariableNumber() const
{
    return variableNumber;
}

bool Clause::isVide() const
{
    return (size() == 0);
}

bool Clause::contientLiteralVrai() const
{
    for(Literal* l : literaux)
        if(l->isAssigned() && l->getVal())
            return true;

    return false;
}

void Clause::supprimerLiterauxFaux()
{
    for(Literal* l : literaux)
        if(l->isAssigned() && (!l->getVal()))
            literaux.erase(l);
}

bool operator==(Clause const &a, Clause const& b)
{
    if(a.size() != b.size())
        return false;

    unordered_set<Literal*> literauxA(a.getLiteraux());
    unordered_set<Literal*> literauxB(b.getLiteraux());

    for(Literal* l : literauxA)
        if(literauxB.erase(l) == 0)
            return false;

    return literauxB.size() == 0;
}
