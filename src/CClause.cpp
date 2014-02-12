#include "CClause.h"
#include<algorithm>
#include<iostream>

using namespace std;

bool egalite_clauses(CClause const* a, CClause const* b) ///Ca aurait pu être utile
{
    return (*a==*b);
}

bool comp(const CLiteral* a, const CLiteral* b) ///Idem
{
    return a->getId()<b->getId();
}

bool comp_lit(const CLiteral* a, const CLiteral* b) /**Un peu subtil, a servi par le passe.
Avant de me mettre aux unordered_set, j'ai utilisé des set. Et avant cela des vector.
Et pour gagner un peu de temps, j'avais le bon gout de trier mes vectors Selon cet ordre ou le précédent.
**/
{
    if(a->getAbsId()==b->getAbsId())
        return a->getId()>b->getId();

    return a->getAbsId()<b->getAbsId();
}


CClause::~CClause()
{}

void CClause::print() const ///Pour le debugage
{
    for(CLiteral* c : literaux)
    {
        c->print();
        cout<<" ";
    }
    cout<<endl;
}

void CClause::supprimer(CLiteral* l) ///Supprime toutes les occurences d'un litéral.
{
    literaux.erase(l);
    n=literaux.size();
}

unordered_set<CLiteral*> CClause::getLiteraux() const
{
    return literaux;
}

int CClause::polariteLiteral(CLiteral* l1, CLiteral* l2) const ///Utile pour distinguer les deux parties pour les mariages.
{
    if(literaux.count(l1)!=0)
        return 1;
    else if(literaux.count(l2)!=0)
        return -1;
    return 0;
}

void CClause::fusionner(CClause* c) /** Fusionne la clause avec une autre.
L'utilisation des pointeurs sur les literaux assure (grace à la méthode insert) qu'il n'y a pas de doublons.
**/
{
    unordered_set<CLiteral*> lit(c->getLiteraux());

    for(CLiteral* l : lit)
        literaux.insert(l);
}

bool CClause::isTautologie() const ///Test simplement si un literal apparait avec les deux polatités.
{
    vector<bool> found_pos(V,false);
    vector<bool> found_neg(V,false);

    for(CLiteral* l : literaux)
    {
        if(l->getId()>0)
            found_pos[l->getId()-1]=true;
        else
            found_neg[-l->getId()-1]=true;
    }

    for(int i=0;i<V;++i)
        if(found_neg[i] && found_pos[i])
            return true;

    return false;
}

void CClause::literalPresent(int id, bool& found_pos, bool& found_neg) const /**Test la présence d'une variable et de sa négation.
On obtient le retour grace aux références en argument. On obtient ainsi la polarite.
**/
{
    for(CLiteral* l : literaux)
    {
        if(l->getPolarite() && l->getId()==id)
            found_pos=true;
        else if(l->getId()==id)
            found_neg=true;
    }
}

void CClause::literauxPresents(vector<bool>& found_pos, vector<bool>& found_neg) const /** Idem que précédemment mais avec
toutes les variables
**/
{
    for(CLiteral* l : literaux)
    {
        if(l->getPolarite())
            found_pos[l->getId()-1];
        else
            found_neg[-l->getId()-1];
    }
}

int CClause::indiceMax() const ///Donne l'indice maximum des variables de la clause (pour ranger dans les seaux).
{
    int sup=0;

    for(CLiteral* l : literaux)
        if(*l>sup)
            sup=l->getAbsId();

    return sup;
}

int CClause::eval() const /**Evalue une clause
Renvoie 0 si la clause est fausse.
1 si la clause est vraie.
2 si une variable n'est pas encore initialisée.
NB : 1 peut être renvoyé alors que certaines variables ne sont pas encore définies.
**/
{
    for(CLiteral* l : literaux)
    {
        if(!l->isAssigned())
            return 2;
        else if(l->getVal())
            return 1;
    }
    return 0;
}

bool CClause::estSurclause(const CClause* c) const ///Test si la clause est une surclause de la clause donnée en argument.
{
    unordered_set<CLiteral*> lit(c->getLiteraux());

    for(CLiteral* l : literaux)
        lit.erase(l);

    return lit.size()==0;
}

int CClause::size() const
{
    return n;
}

int CClause::getV() const
{
    return V;
}

bool CClause::isVide() const
{
    return (n==0);
}

CClause::CClause(const CClause& other) : literaux(other.literaux), V(other.V), n(other.n)
{}

CClause::CClause() : literaux(unordered_set<CLiteral*>()), V(0), n(0)
{}

CClause::CClause(unordered_set<CLiteral*> e, int V_e) : literaux(e), V(V_e), n(e.size())
{}

bool operator==(CClause const &a_, CClause const& b_)
{
    CClause a(a_);
    CClause b(b_);
    if(a.size()!=b.size())
        return false;

    unordered_set<CLiteral*> t(a.getLiteraux());
    unordered_set<CLiteral*> u(b.getLiteraux());

    for(CLiteral* l : t)
        if(u.erase(l)==0)
            return false;

    if(u.size()!=0)
        return false;

    return true;
}
