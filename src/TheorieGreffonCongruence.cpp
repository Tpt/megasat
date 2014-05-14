#include "../include/TheorieGreffonCongruence.h"

using namespace std;

TheorieGreffonCongruence::TheorieGreffonCongruence() : atomes(vector<AtomeCongruence>()), substitutions(vector<map<int, Terme>>())
{}

TheorieGreffonCongruence::~TheorieGreffonCongruence()
{}

TheorieGreffonCongruence::TheorieGreffonCongruence(const TheorieGreffonCongruence& F) : atomes(F.atomes), substitutions(F.substitutions)
{}

TheorieGreffonCongruence& TheorieGreffonCongruence::operator= (const TheorieGreffonCongruence& other)
{
    TheorieGreffonCongruence Temp(other);

    swap(Temp.atomes, this->atomes);
    swap(Temp.substitutions, this->substitutions);

    return *this;
}

vector<int> TheorieGreffonCongruence::onAssignation(int id, unsigned int niveau)
{
    cout<<endl<<endl<<"entre ici :"<<id<<" "<<niveau<<endl;
    for(unsigned int i=0;i<atomes.size();++i)
        cout<<i<<" "<<atomes[i].toString()<<endl;

    TheorieGreffonSimple::onAssignation(id, niveau);
    if(static_cast<unsigned int>(abs(id)) > atomes.size())
        return vector<int>();

    if(niveau >= substitutions.size())
    {
        substitutions.resize(niveau + 1);
    }
    cout<<"B"<<endl;
    AtomeCongruence atomeSubstitue(appliquerSubstitutions(static_cast<unsigned int>(id > 0 ? id : -id)));
    cout<<"B"<<endl;

    vector<int> clauseAApprendre;
    unsigned long nombreDeVariablesAtomes = (atomes.size() < valVariables.size()) ? atomes.size() : valVariables.size();
    for(unsigned int i = 0; i < nombreDeVariablesAtomes; i++)
        if(valVariables[i] == VRAI)
            clauseAApprendre.push_back(-static_cast<int>(i) - 1);
    cout<<"B"<<endl;

    for(unsigned int i=0;i<substitutions.size();++i)
    {
        cout<<i<<": "<<endl;
        for(pair<int, Terme> t : substitutions[i])
            cout<<"    "<<t.first<<" "<<t.second.toString()<<endl;
    }

    cout<<atomeSubstitue.toString()<<endl;
    cout<<atomeSubstitue.isConflit()<<endl;

    if(atomeSubstitue.isConflit())
    {
        cout<<"Il y a un conflit !"<<endl;
        if(id > 0)
        {
            cout<<"id > 0"<<endl;
            return clauseAApprendre;
        }
        else
        {
            cout<<"id < 0"<<endl;
            return vector<int>();
        }
    }
    else
    {
        cout<<"Il n'y a pas de conflit !"<<endl;
        if(id < 0)
        {
            cout<<"id < 0"<<endl;
            clauseAApprendre.push_back(id);
            cout<<"Et tout va très bien !"<<endl;
            return clauseAApprendre;
        }
    }
    cout<<"B"<<endl;
    if(id > 0)
    {
        cout<<"On va se la faire, cette unification !"<<endl;
        map<int, Terme> subst;

        try
        {
            AtomeCongruence yetAnotherAtome(appliquerSubstitutions(static_cast<unsigned int>(id)));
            cout<<"Et on va unifier : "<<yetAnotherAtome.toString()<<endl;
            subst=unify(yetAnotherAtome);
            cout<<"Et on a une unification de taille : "<<subst.size()<<endl;
        }
        catch(nonUnifiableException& a)
        {
            cout<<"SOS ! On a ne excepton !"<<endl;
            return clauseAApprendre;
        }

        for(pair<int, Terme> s : subst)
        {
            cout<<s.first<<" "<<s.second.toString()<<endl;
            substitutions[niveau][s.first] = s.second;
        }

        for(unsigned int i = 0; i < nombreDeVariablesAtomes; i++)
            if(valVariables[i] == FAUX)
                if(!appliquerSubstitutions(i).isConflit())
                {
                    clauseAApprendre.push_back(static_cast<int>(i) + 1);
                    return clauseAApprendre;
                }
    }
    cout<<"B"<<endl;
    return vector<int>();
}

map<int, Terme> TheorieGreffonCongruence::unify(AtomeCongruence atome) const
{
    map<int, Terme> sub;
    try
    {
        sub = unify(atome.getGauche(), atome.getDroite());
        return sub;
    }
    catch(nonUnifiableException& a)
    {
        throw;
    }
    return map<int, Terme>();
}

AtomeCongruence TheorieGreffonCongruence::appliquerSubstitutions(unsigned int id) const
{
    cout<<"C "<<id<<" "<<atomes.size()<<endl;
    return AtomeCongruence(*appliquerSubstitutions(atomes[id-1].getGauche()), *appliquerSubstitutions(atomes[id-1].getDroite()));
}

Terme* TheorieGreffonCongruence::appliquerSubstitutions(Terme terme) const
{
    cout<<"D"<<endl;
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

void TheorieGreffonCongruence::onBacktrack(unsigned int l)
{
    TheorieGreffonSimple::onBacktrack(l);
    substitutions.erase(substitutions.begin() + static_cast<int>(l), substitutions.end());
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
    cout<<gauche.toString()<<endl;
    cout<<droite.toString()<<endl;
    map<int, Terme> sub;
    try
    {
        sub = iterate(map<int, Terme>(), vector<pair<Terme*, Terme*>>(1,make_pair(&gauche, &droite)));
        return sub;
    }
    catch(nonUnifiableException& a)
    {
        throw;
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
    Terme* b = ab.second;

    cout<<a->toString()<<endl;
    cout<<b->toString()<<endl;

    if(a->isVariable() && b->isVariable() && a->getVariable()==b->getVariable())
    {
        cout<<"Ce sont deux variables identiques"<<endl;
        return iterate(subst, contraintes);
    }

    if(a->isFonction() && b->isFonction() && a->getSymbole()!=b->getSymbole())
    {
        cout<<"Ce sont deux fonctions différentes"<<endl;
        throw nonUnifiableException();
    }


    if(a->isFonction() && b->isFonction() && a->getParametres().size()!=b->getParametres().size())
    {
        cout<<"Ce sont deux fonctions identiques mais d'arités différentes"<<endl;
        throw nonUnifiableException();
    }


    if(a->isFonction() && b->isFonction())
    {
        cout<<"Ce sont deux fonctions identiques"<<endl;
        for(unsigned int i=0; i<a->getParametres().size(); ++i)
            contraintes.push_back(pair<Terme*, Terme*>(a->getParametres()[i], b->getParametres()[i]));
        return iterate(subst, contraintes);
    }

    if(b->isVariable())
    {
        cout<<"Seulement b est une variable"<<endl;
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
        cout<<"Seulement a est une variable"<<endl;
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
