#include "../include/TheorieGreffonCongruence.h"

using namespace std;

TheorieGreffonCongruence::TheorieGreffonCongruence() :
atomes(vector<AtomeCongruence>()), substitutions(vector<map<int, Terme>>())
{}

TheorieGreffonCongruence::~TheorieGreffonCongruence()
{}

vector<int> TheorieGreffonCongruence::onAssignation(int id, unsigned int niveau)
{
#ifdef DEBUG
    cout<<endl<<"Entre ici dans le solveur de congruence avec le litéral "<<id<<" au niveau "<<niveau<<endl;
#endif

    TheorieGreffonSimple::onAssignation(id, niveau);
    if(static_cast<unsigned int>(abs(id)) > atomes.size())
    {
#ifdef DEBUG
        cout<<"La variable ne correspond pas un terme."<<endl;
#endif
        return vector<int>();
    }

#ifdef DEBUG
    cout<<"On regarde le terme : "<<atomes[static_cast<unsigned int>(abs(id)-1)].toString()<<endl;
#endif

    if(niveau >= substitutions.size())
    {
        substitutions.resize(niveau + 1);
    }
    AtomeCongruence atomeSubstitue(appliquerSubstitutions(static_cast<unsigned int>(abs(id))));

    vector<int> clauseAApprendre;
    unsigned long nombreDeVariablesAtomes = (atomes.size() < valVariables.size()) ? atomes.size() : valVariables.size();
    for(unsigned int i = 0; i < nombreDeVariablesAtomes; i++)
        if(valVariables[i] == VRAI)
            clauseAApprendre.push_back(-static_cast<int>(i) - 1);

    if(atomeSubstitue.isConflit())
    {
        if(id > 0 && atomeSubstitue.isConflitInsurmontable())
        {
#ifdef DEBUG
            cout<<"Il y a un conflit non unifiable : échec"<<endl;
#endif
            return clauseAApprendre;
        }
        else if(id < 0)
        {
#ifdef DEBUG
            cout<<"Il y a un conflit sur un terme qui n'est pas à unifier : succes"<<endl;
#endif
            return vector<int>();
        }
    }
    else
    {
        if(id < 0)
        {
            clauseAApprendre.push_back(-id);
#ifdef DEBUG
            cout<<"Un terme faux n'a pas de conflit : échec"<<endl;
#endif
            return clauseAApprendre;
        }
    }
    if(id > 0)
    {
#ifdef DEBUG
        cout<<"On unifie le terme."<<endl;
#endif
        map<int, Terme> subst;

        try
        {
            AtomeCongruence yetAnotherAtome(appliquerSubstitutions(static_cast<unsigned int>(id)));
            subst=unify(yetAnotherAtome);
#ifdef DEBUG
            cout<<"Succès de l'unification."<<endl<<"Substitution(s) générée(s) : "<<endl;
#endif
        }
        catch(nonUnifiableException& a)
        {
#ifdef DEBUG
            cout<<"Le terme est non unifiable : échec"<<endl;
#endif
            return clauseAApprendre;
        }

        for(pair<int, Terme> s : subst)
        {
#ifdef DEBUG
            cout<<"x_"<<s.first<<" -> "<<s.second.toString()<<endl;
#endif
            substitutions[niveau][s.first] = s.second;
        }

        for(unsigned int i = 0; i < nombreDeVariablesAtomes; i++)
            if(valVariables[i] == FAUX)
                if(!appliquerSubstitutions(i+1).isConflit())
                {
                    clauseAApprendre.push_back(static_cast<int>(i) + 1);
                    return clauseAApprendre;
                }
    }
    return vector<int>();
}

map<int, Terme> TheorieGreffonCongruence::unify(const AtomeCongruence& atome) const
{
    return unify(atome.getGauche(), atome.getDroite());
}

AtomeCongruence TheorieGreffonCongruence::appliquerSubstitutions(unsigned int id) const
{
    return AtomeCongruence(appliquerSubstitutions(atomes[id-1].getGauche()), appliquerSubstitutions(atomes[id-1].getDroite()));
}

Terme TheorieGreffonCongruence::appliquerSubstitutions(const Terme& terme) const
{
    vector<Terme> parametres;

    if(terme.getParametres().empty())
        goto traitement_des_variables;

    for(Terme t : terme.getParametres())
        parametres.push_back(appliquerSubstitutions(t));

    return Terme(terme.getSymbole(), parametres);

    traitement_des_variables :

    for(map<int, Terme> subst : substitutions)
        for(pair<int, Terme> s : subst)
            if(terme.getVariable() == s.first)
                return appliquerSubstitutions(s.second);

    return terme;
}

void TheorieGreffonCongruence::onBacktrack(unsigned int l)
{
    TheorieGreffonSimple::onBacktrack(l);
    if(substitutions.size() >= l)
        substitutions.erase(substitutions.begin() + static_cast<int>(l), substitutions.end());
}

bool TheorieGreffonCongruence::appear(int variable, const Terme& terme) const
{
    if(terme.isVariable())
        return variable==terme.getVariable();

    for(Terme t : terme.getParametres())
        if(appear(variable, t))
            return true;

    return false;
}

Terme TheorieGreffonCongruence::replace(int variable, const Terme& u, const Terme& filtre) const
{
    if(filtre.isVariable())
    {
        if(filtre.getVariable() == variable)
            return u;
        else
            return filtre;
    }

    vector<Terme> parametres;

    for(Terme t : filtre.getParametres())
        parametres.push_back(replace(variable, u, t));

    return Terme(filtre.getSymbole(), parametres);
}

map<int, Terme> TheorieGreffonCongruence::unify(const Terme& gauche, const Terme& droite) const
{
    map<int, Terme> sub;
    try
    {
        sub = iterate(map<int, Terme>(), vector<pair<Terme, Terme>>(1, make_pair(gauche, droite)));
        return sub;
    }
    catch(nonUnifiableException& a)
    {
        throw;
    }
    return map<int, Terme>();
}

map<int, Terme> TheorieGreffonCongruence::iterate(map<int, Terme> subst, vector<pair<Terme, Terme>> contraintes) const
{
    if(contraintes.empty())
        return subst;

    pair<Terme, Terme> ab = contraintes[contraintes.size()-1];
    contraintes.pop_back();

    Terme a = ab.first;
    Terme b = ab.second;


    if(a.isVariable() && b.isVariable() && a.getVariable()==b.getVariable())
    {
        return iterate(subst, contraintes);
    }

    if(a.isFonction() && b.isFonction() && a.getSymbole()!=b.getSymbole())
    {
        throw nonUnifiableException();
    }


    if(a.isFonction() && b.isFonction() && a.getParametres().size()!=b.getParametres().size())
    {
        throw nonUnifiableException();
    }


    if(a.isFonction() && b.isFonction())
    {
        for(unsigned int i=0; i<a.getParametres().size(); ++i)
            contraintes.push_back(pair<Terme, Terme>(a.getParametres()[i], b.getParametres()[i]));
        return iterate(subst, contraintes);
    }

    if(b.isVariable())
    {
        if(appear(b.getVariable(), a))
            throw nonUnifiableException();
        vector<pair<Terme, Terme>> nouvellesContraintes;
        subst[b.getVariable()]=a;
        for(pair<Terme, Terme> e : contraintes)
        {
            nouvellesContraintes.push_back(pair<Terme, Terme>(replace(b.getVariable(), a, e.first),replace(b.getVariable(), a, e.second)));
        }
        return iterate(subst, nouvellesContraintes);
    }

    if(a.isVariable())
    {
        if(appear(a.getVariable(), b))
            throw nonUnifiableException();
        vector<pair<Terme, Terme>> nouvellesContraintes;
        subst[a.getVariable()]=b;
        for(pair<Terme, Terme> e : contraintes)
        {
            nouvellesContraintes.push_back(pair<Terme, Terme>(replace(a.getVariable(), b, e.first),replace(a.getVariable(), b, e.second)));
        }
        return iterate(subst, nouvellesContraintes);
    }
    return map<int, Terme>();
}
