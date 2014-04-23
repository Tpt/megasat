#include "../include/ConstructeurPreuve.h"
#include<algorithm>
#include<iostream>

using namespace std;

ConstructeurPreuve::ConstructeurPreuve(vector<pair<int,vector<int>>> graphe_) :
graphe(graphe_), preuve(construirePreuve())
{}

ConstructeurPreuve::~ConstructeurPreuve()
{}

Preuve ConstructeurPreuve::construirePreuve() const
{
    int literalCourant = graphe[graphe.size()-1].first;
    Preuve p = Preuve(graphe[graphe.size()-1].second, rechercherClauseAssignantLiteral(-literalCourant), literalCourant);
    vector<int> variables(variablesNiveauCourant());
    vector<int> variablesRestantes(variablesNiveauCourantRestantes(variables, p.getConclusion()));

    while(variablesRestantes.size() > 0)
    {
        literalCourant = variablesRestantes[variablesRestantes.size()-1];
        p = Preuve(p, rechercherClauseAssignantLiteral(-literalCourant), literalCourant);
        variablesRestantes = variablesNiveauCourantRestantes(variables, p.getConclusion());
    }

    return p;
}

vector<int> ConstructeurPreuve::variablesNiveauCourant() const
{
    vector<int> sortie;

    for(pair<int, vector<int>> e : graphe)
        if(e.second.size()>0)
            sortie.push_back(e.first);

    return sortie;
}

vector<int> ConstructeurPreuve::variablesNiveauCourantRestantes(const vector<int>& variables, const vector<int>& clause) const
{
    vector<int> sortie(0);

    for(int lit : clause)
        if(find(variables.begin(), variables.end(), -lit) != variables.end())
            sortie.push_back(lit);

    return sortie;
}

vector<int> ConstructeurPreuve::rechercherClauseAssignantLiteral(int id) const
{
    for(pair<int,vector<int>> e : graphe)
        if(e.first == id)
            return e.second;

    return vector<int>(0);
}
