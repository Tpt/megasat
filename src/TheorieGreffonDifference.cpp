#include "../include/TheorieGreffonDifference.h"

using namespace std;

typedef vector<vector<vector<pair<int,int>>>> type_adjacence;

TheorieGreffonDifference::TheorieGreffonDifference() : atomes(vector<AtomeDifference>()), adjacence(type_adjacence()), varIdMax(0)
{}

void TheorieGreffonDifference::setCorrespondanceAtomes(const std::vector<AtomeDifference>& corr) {
    atomes = corr;

    for(unsigned int i = 0; i <= atomes.size(); i++)
        variablePerAtome[atomes[i]] = i + 1;

    for( AtomeDifference atome : atomes ) {
        if(atome.getI() > varIdMax)
            varIdMax = atome.getI();
        if(atome.getJ() > varIdMax)
            varIdMax = atome.getJ();
    }

    adjacence = type_adjacence(varIdMax + 1);
};

vector<int> TheorieGreffonDifference::onAssignation(int id, unsigned int niveau)
{
    TheorieGreffonSimple::onAssignation(id, niveau);
    if(static_cast<unsigned int>(abs(id)) > atomes.size())
        return vector<int>();

    if(niveau >= adjacence[0].size())
    {
        for(int i = 0; i <= varIdMax; i++)
            adjacence[i].resize(niveau + 1);
    }

    AtomeDifference atomeAssigne = atomes[abs(id) - 1];
    if(id > 0)
        adjacence[atomeAssigne.getI()][niveau].push_back(pair<int,int>(atomeAssigne.getJ(), atomeAssigne.getN()));
    else //si non(xi - xj <= n) -> xi - xj > n -> xj - xi < -n -> xj - xi <= -n -1
        adjacence[atomeAssigne.getJ()][niveau].push_back(pair<int,int>(atomeAssigne.getI(), -atomeAssigne.getN() - 1));
        

    vector<AtomeDifference> cycle = testePresenceCycleDePoidsNegatif(atomeAssigne.getI());
    if(cycle.empty())
        return vector<int>(0);

    vector<int> clauseAAjouter(cycle.size());
    for(unsigned int i = 0; i < cycle.size(); i++) {
        clauseAAjouter[i] = -variablePerAtome[cycle[i]];
    }

    return clauseAAjouter;
}

vector<AtomeDifference> TheorieGreffonDifference::testePresenceCycleDePoidsNegatif(int depart)
{
    vector<int> poids( varIdMax + 1, INT_MAX );
    poids[depart] = 0;
    vector<int> changes( varIdMax + 1, 0 );
    
    for(unsigned int i = 1; i <= varIdMax; i++) {
        bool nothingChanged = true;
        for(unsigned int sommet = 0; sommet <= varIdMax; sommet++)
        {
            if(changes[sommet] == i - 1)
            {
                for(vector<pair<int,int>>& sacNiveau : adjacence[sommet])
                    for(pair<int,int> arete : sacNiveau)
                    {
                        int nouveauPoids = poids[sommet] + arete.second;
                        if(nouveauPoids < poids[arete.first])
                        {
                            poids[arete.first] = nouveauPoids;
                            changes[arete.first] = i;
                            nothingChanged = false;
                        }
                    }
            }
            if(nothingChanged)
                return vector<AtomeDifference>();
        }
    }

    //Recherche de cycles
    vector<AtomeDifference> aretesProblemes;
    for(unsigned int sommet = 0; sommet <= varIdMax; sommet++)
        for(vector<pair<int,int>>& sacNiveau : adjacence[sommet])
            for(pair<int,int> arete : sacNiveau)
                if(poids[sommet] + arete.second < poids[arete.first])
                    aretesProblemes.push_back(AtomeDifference(sommet, arete.first, arete.second));

    return aretesProblemes;
}

void TheorieGreffonDifference::onBacktrack(unsigned int l)
{
    TheorieGreffonSimple::onBacktrack(l);

    for(int i = 0; i <= varIdMax; i++)
        adjacence[i].erase(adjacence[i].begin() + static_cast<int>(l), adjacence[i].end());
}