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
    cout<<endl<<endl<<"entre ici :"<<id<<" "<<niveau<<endl;
    for(unsigned int i = 0; i < atomes.size(); ++i)
        cout<<i<<" "<<atomes[i].toString()<<endl;
#endif

    TheorieGreffonSimple::onAssignation(id, niveau);
    if(static_cast<unsigned int>(abs(id)) > atomes.size())
        return vector<int>();

    if(niveau >= substitutions.size())
    {
        substitutions.resize(niveau + 1);
    }
#ifdef DEBUG
    cout<<"B"<<endl;
#endif
    AtomeCongruence atomeSubstitue(appliquerSubstitutions(static_cast<unsigned int>(abs(id))));
#ifdef DEBUG
    cout<<"B"<<endl;
#endif

    vector<int> clauseAApprendre;
    unsigned long nombreDeVariablesAtomes = (atomes.size() < valVariables.size()) ? atomes.size() : valVariables.size();
    for(unsigned int i = 0; i < nombreDeVariablesAtomes; i++)
        if(valVariables[i] == VRAI)
            clauseAApprendre.push_back(-static_cast<int>(i) - 1);
#ifdef DEBUG
    cout<<"B"<<endl;


    for(unsigned int i = 0; i < substitutions.size();++i)
    {
        cout<<i<<": "<<endl;
        for(pair<int, Terme> t : substitutions[i])
            cout<<"    x_"<<t.first<<" -> "<<t.second.toString()<<endl;
    }
    cout<<"C'est tout !"<<endl;
    cout<<atomeSubstitue.toString()<<endl;
    cout<<"B"<<endl;
    cout<<atomeSubstitue.isConflit()<<endl;
#endif

    if(atomeSubstitue.isConflit())
    {
#ifdef DEBUG
        cout<<"Il y a un conflit !"<<endl;
#endif
        if(id > 0 && atomeSubstitue.isConflitInsurmontable())
        {
#ifdef DEBUG
            cout<<"id > 0"<<endl;
#endif
            return clauseAApprendre;
        }
        else if(id < 0)
        {
#ifdef DEBUG
            cout<<"id < 0"<<endl;
#endif
            return vector<int>();
        }
    }
    else
    {
#ifdef DEBUG
        cout<<"Il n'y a pas de conflit !"<<endl;
#endif

        if(id < 0)
        {
#ifdef DEBUG
            cout<<"id < 0"<<endl;
#endif
            clauseAApprendre.push_back(id);
#ifdef DEBUG
            cout<<"Et tout va très bien !"<<endl;
#endif
            return clauseAApprendre;
        }
    }
#ifdef DEBUG
    cout<<"B"<<endl;
#endif
    if(id > 0)
    {
#ifdef DEBUG
        cout<<"On va se la faire, cette unification !"<<endl;
#endif
        map<int, Terme> subst;

        try
        {
            AtomeCongruence yetAnotherAtome(appliquerSubstitutions(static_cast<unsigned int>(id)));
#ifdef DEBUG
            cout<<"Et on va unifier : "<<yetAnotherAtome.toString()<<endl;
#endif
            subst=unify(yetAnotherAtome);
#ifdef DEBUG
            cout<<"Et on a une unification de taille : "<<subst.size()<<endl;
#endif
        }
        catch(nonUnifiableException& a)
        {
#ifdef DEBUG
            cout<<"SOS ! On a une exception !"<<endl;
#endif
            return clauseAApprendre;
        }

        for(pair<int, Terme> s : subst)
        {
#ifdef DEBUG
            cout<<s.first<<" "<<s.second.toString()<<endl;
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
#ifdef DEBUG
    cout<<"B"<<endl;
#endif
    return vector<int>();
}

map<int, Terme> TheorieGreffonCongruence::unify(const AtomeCongruence& atome) const
{
    return unify(atome.getGauche(), atome.getDroite());
}

AtomeCongruence TheorieGreffonCongruence::appliquerSubstitutions(unsigned int id) const
{
#ifdef DEBUG
    cout<<"C "<<id<<" "<<atomes.size()<<endl;
#endif
    return AtomeCongruence(appliquerSubstitutions(atomes[id-1].getGauche()), appliquerSubstitutions(atomes[id-1].getDroite()));
}

Terme TheorieGreffonCongruence::appliquerSubstitutions(const Terme terme) const
{
#ifdef DEBUG
    cout<<" R: "<<terme.toString()<<endl;
#endif

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
#ifdef DEBUG
    cout<<gauche.toString()<<endl;
    cout<<droite.toString()<<endl;
#endif
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

map<int, Terme> TheorieGreffonCongruence::iterate(const map<int, Terme>& subst, vector<pair<Terme, Terme>> contraintes) const
{
    if(contraintes.empty())
        return subst;

    pair<Terme, Terme> ab = contraintes[contraintes.size()-1];
    contraintes.pop_back();

    Terme a = ab.first;
    Terme b = ab.second;

#ifdef DEBUG
    cout<<a.toString()<<endl;
    cout<<b.toString()<<endl;
#endif

    if(a.isVariable() && b.isVariable() && a.getVariable()==b.getVariable())
    {
#ifdef DEBUG
        cout<<"Ce sont deux variables identiques"<<endl;
#endif
        return iterate(subst, contraintes);
    }

    if(a.isFonction() && b.isFonction() && a.getSymbole()!=b.getSymbole())
    {
#ifdef DEBUG
        cout<<"Ce sont deux fonctions différentes"<<endl;
#endif
        throw nonUnifiableException();
    }


    if(a.isFonction() && b.isFonction() && a.getParametres().size()!=b.getParametres().size())
    {
#ifdef DEBUG
        cout<<"Ce sont deux fonctions identiques mais d'arités différentes"<<endl;
#endif
        throw nonUnifiableException();
    }


    if(a.isFonction() && b.isFonction())
    {
#ifdef DEBUG
        cout<<"Ce sont deux fonctions identiques"<<endl;
#endif
        for(unsigned int i=0; i<a.getParametres().size(); ++i)
            contraintes.push_back(pair<Terme, Terme>(a.getParametres()[i], b.getParametres()[i]));
        return iterate(subst, contraintes);
    }

    if(b.isVariable())
    {
#ifdef DEBUG
        cout<<"Seulement b est une variable"<<endl;
#endif
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
#ifdef DEBUG
        cout<<"Seulement a est une variable"<<endl;
#endif
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
