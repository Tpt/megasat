#include "../include/TheorieGreffonCongruence.h"

using namespace std;

TheorieGreffonCongruence::TheorieGreffonCongruence() :
formule(nullptr), atomes(vector<AtomeCongruence>()), substitutions(vector<map<int, Terme>>())
{}

TheorieGreffonCongruence::~TheorieGreffonCongruence()
{}

TheorieGreffonCongruence::TheorieGreffonCongruence(const TheorieGreffonCongruence& F) :
formule(F.formule), atomes(F.atomes), substitutions(F.substitutions)
{}

TheorieGreffonCongruence& TheorieGreffonCongruence::operator= (const TheorieGreffonCongruence& other)
{
    TheorieGreffonCongruence Temp(other);

    swap(Temp.formule, this->formule);
    swap(Temp.atomes, this->atomes);
    swap(Temp.substitutions, this->substitutions);

    return *this;
}

vector<int> TheorieGreffonCongruence::onAssignation(unsigned int id, unsigned int niveau)
{
    (void) id;

    if(niveau>=substitutions.size())
    {
        substitutions.resize(niveau+1);
    }

    appliquerSubstitutions(id);

    return vector<int>();
}

AtomeCongruence TheorieGreffonCongruence::appliquerSubstitutions(unsigned int id) const
{
    return AtomeCongruence(*appliquerSubstitutions(atomes[id].getGauche()), *appliquerSubstitutions(atomes[id].getDroite()));
}

Terme* TheorieGreffonCongruence::appliquerSubstitutions(Terme terme) const
{
    return appliquerSubstitutions(&terme);
}

Terme* TheorieGreffonCongruence::appliquerSubstitutions(Terme* terme) const
{
    vector<Terme*> parametres;

    if(terme->getParametres().size()==0)
        goto traitement_des_variables;

    for(Terme* t : terme->getParametres())
        parametres.push_back(appliquerSubstitutions(t));

    return new Terme(terme->getSymbole(), parametres);

    traitement_des_variables :

    for(map<int, Terme> subst : substitutions)
        for(pair<int, Terme> s : subst)
            if(terme->getVariable()==s.first)
                return appliquerSubstitutions(s.second);

    return terme;
}

void TheorieGreffonCongruence::onBeginning(Formule* formule_)
{
    formule=formule_;
}

void TheorieGreffonCongruence::onBacktrack(unsigned int l)
{
    substitutions.erase(substitutions.begin()+l, substitutions.end());
}


bool TheorieGreffonCongruence::appear(int variable, Terme* terme) const
{
    if(terme->isVariable())
        return variable==terme->getVariable();

    for(Terme* t : terme->getParametres())
        if(appear(variable, t))
            return true;

    return false;
}

Terme* TheorieGreffonCongruence::replace(int variable, Terme* u, Terme* filtre) const
{
    if(filtre->isVariable())
    {
        if(filtre->getVariable() == variable)
            return new Terme(*u);
        else
            return new Terme(*filtre);
    }

    vector<Terme*> parametres;

    for(Terme* t : filtre->getParametres())
        parametres.push_back(replace(variable, u, t));

    return new Terme(filtre->getSymbole(), parametres);
}

map<int, Terme> TheorieGreffonCongruence::unify(Terme gauche, Terme droite) const
{
    map<int, Terme> sub;
    try
    {
        sub = iterate(map<int, Terme>(), vector<pair<Terme*, Terme*>>(1,pair<Terme*, Terme*>(&gauche, &droite)));
        return sub;
    }
    catch(nonUnifiableException& a)
    {

    }
    return map<int, Terme>();
}

map<int, Terme> TheorieGreffonCongruence::iterate(map<int, Terme> subst, vector<pair<Terme*, Terme*>> contraintes) const
{
    if(contraintes.size()==0)
        return subst;

    pair<Terme*, Terme*> ab = contraintes[contraintes.size()-1];
    contraintes.pop_back();

    Terme* a = ab.first;
    Terme* b = ab.first;

    if(a->isVariable() && b->isVariable() && a->getVariable()==b->getVariable())
        return iterate(subst, contraintes);

    if(a->isFonction() && b->isFonction() && a->getSymbole()!=b->getSymbole())
        throw nonUnifiableException();

    if(a->isFonction() && b->isFonction() && a->getParametres().size()!=b->getParametres().size())
        throw nonUnifiableException();

    if(a->isFonction() && b->isFonction())
    {
        for(unsigned int i=0; i<a->getParametres().size(); ++i)
            contraintes.push_back(pair<Terme*, Terme*>(a->getParametres()[i], b->getParametres()[i]));
        return iterate(subst, contraintes);
    }

    if(b->isVariable())
    {
        if(appear(b->getVariable(), a))
            throw nonUnifiableException();
        vector<pair<Terme*, Terme*>> nouvellesContraintes;
        subst[b->getVariable()]=*a;
        for(pair<Terme*, Terme*> e : contraintes)
        {
            nouvellesContraintes.push_back(pair<Terme*, Terme*>(replace(b->getVariable(), a, e.first),replace(b->getVariable(), a, e.second)));
        }
        return iterate(subst, nouvellesContraintes);
    }

    if(a->isVariable())
    {
        if(appear(a->getVariable(), b))
            throw nonUnifiableException();
        vector<pair<Terme*, Terme*>> nouvellesContraintes;
        subst[a->getVariable()]=*b;
        for(pair<Terme*, Terme*> e : contraintes)
        {
            nouvellesContraintes.push_back(pair<Terme*, Terme*>(replace(a->getVariable(), b, e.first),replace(a->getVariable(), b, e.second)));
        }
        return iterate(subst, nouvellesContraintes);
    }
    return map<int, Terme>();
}
