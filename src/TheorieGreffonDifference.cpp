#include "../include/TheorieGreffonDifference.h"
#include<climits>
#include<stack>
#include<set>

using namespace std;

typedef vector<vector<vector<pair<unsigned int,int>>>> type_adjacence;

TheorieGreffonDifference::TheorieGreffonDifference() :
atomes(vector<AtomeDifference>()), literalPerAtome(unordered_map<AtomeDifference,int>()), adjacence(type_adjacence(0)), varIdMax(0)
{}

void TheorieGreffonDifference::setCorrespondanceAtomes(const std::vector<AtomeDifference>& corr) {
    atomes = corr;

    for(unsigned int i = 0; i < atomes.size(); i++)
    {
        AtomeDifference atome = atomes[i];
        literalPerAtome[atome] = static_cast<int>(i) + 1;
        literalPerAtome[AtomeDifference(atome.getJ(), atome.getI(), -atome.getN() - 1)] = -static_cast<int>(i) - 1;
    }

    varIdMax = 0;
    for(AtomeDifference atome : atomes) {
        if(atome.getI() > varIdMax)
            varIdMax = atome.getI();
        if(atome.getJ() > varIdMax)
            varIdMax = atome.getJ();
    }

    adjacence = type_adjacence(varIdMax + 1);
}

vector<int> TheorieGreffonDifference::onAssignation(int id, unsigned int niveau)
{
    TheorieGreffonSimple::onAssignation(id, niveau);
    if(static_cast<unsigned int>(abs(id)) > atomes.size())
        return vector<int>(0);

    if(niveau >= adjacence[0].size())
    {
        for(unsigned long i = 0; i <= varIdMax; i++)
            adjacence[i].resize(niveau + 1);
    }

    AtomeDifference atomeAssigne = atomes[static_cast<unsigned int>(abs(id)) - 1];
    if(id > 0)
    {
        adjacence[atomeAssigne.getI()][niveau].push_back(pair<int,int>(atomeAssigne.getJ(), atomeAssigne.getN()));
#ifdef DEBUG
        cout << "c ajout de x" << atomeAssigne.getI() - 1 << " - x" << atomeAssigne.getJ() - 1 << " <= " << atomeAssigne.getN() << " au niveau " << niveau << endl;
#endif
    }
    else //si non(xi - xj <= n) -> xi - xj > n -> xj - xi < -n -> xj - xi <= -n -1
    {
        adjacence[atomeAssigne.getJ()][niveau].push_back(pair<int,int>(atomeAssigne.getI(), -atomeAssigne.getN() - 1));
#ifdef DEBUG
        cout << "c ajout de x" << atomeAssigne.getI() - 1 << " - x" << atomeAssigne.getJ() - 1 << " > " << atomeAssigne.getN() << " au niveau " << niveau << endl;
#endif
    }

    vector<AtomeDifference> cycle = testePresenceCycleDePoidsNegatif(atomeAssigne.getI());

    vector<int> clauseAAjouter(cycle.size());
    for(unsigned int i = 0; i < cycle.size(); i++) {
        clauseAAjouter[i] = -literalPerAtome[cycle[i]];
    }

    return clauseAAjouter;
}

vector<AtomeDifference> TheorieGreffonDifference::testePresenceCycleDePoidsNegatif(unsigned int depart)
{
    vector<int> poids(varIdMax + 1, INT_MAX);
    poids[depart] = 0;
    vector<unsigned int> changes(varIdMax + 1, 0);
    vector<pair<unsigned int, int>> pere(varIdMax + 1);
    for(unsigned int sommet = 0; sommet <= varIdMax; sommet++)
        pere[sommet] = pair<unsigned int,int>(sommet, 0);

    for(unsigned int i = 1; i <= varIdMax + 1; i++) {
        bool nothingChanged = true;
        for(unsigned int sommet = 0; sommet <= varIdMax; sommet++)
        {
            if(changes[sommet] == i - 1)
            {
                for(auto& sacNiveau : adjacence[sommet])
                    for(pair<unsigned int,int>& arete : sacNiveau)
                    {
                        int nouveauPoids = poids[sommet] + arete.second;
                        if(nouveauPoids < poids[arete.first])
                        {
                            poids[arete.first] = nouveauPoids;
                            changes[arete.first] = i;
                            nothingChanged = false;
                            pere[arete.first] = pair<unsigned int,int>(sommet, arete.second);
                        }
                    }
            }
        }
        if(nothingChanged)
            return vector<AtomeDifference>(0);
    }

    //Recherche de l'existance de cycles de poids negatif via un parcours en profondeur sur les parents
    enum COLOR { BLANC, GRIS, NOIR };
    vector<COLOR> coloriage(varIdMax + 1, BLANC);

    for(unsigned int sommetDepart = 0; sommetDepart <= varIdMax; sommetDepart++)
    {
        if(coloriage[sommetDepart] != BLANC)
            continue;
        stack<pair<unsigned int,int>> parcourus;
        parcourus.push(pair<unsigned int, int>(sommetDepart,0));
        unsigned int prochainSommet = sommetDepart;
        while(true) {
            unsigned int sommet = prochainSommet;
            coloriage[sommet] = GRIS;
            pair<unsigned int, int> suivant = pere[sommet];
            parcourus.push(suivant);
            prochainSommet = suivant.first;
            if(prochainSommet == sommet || coloriage[prochainSommet] == NOIR)
                break;
            if(coloriage[prochainSommet] == GRIS)
            {
                vector<AtomeDifference> aretesProblemes;
                while(!parcourus.empty())
                {
                    pair<unsigned int, int> top = parcourus.top();
                    parcourus.pop();
                    if(!parcourus.empty())
                        aretesProblemes.push_back(AtomeDifference(top.first, parcourus.top().first, top.second));
                }
                return aretesProblemes;
            }
        }
        while(!parcourus.empty())
        {
            pair<unsigned int, int> fait = parcourus.top();
            parcourus.pop();
            coloriage[fait.first] = NOIR;
        }
    }

    return vector<AtomeDifference>(0);
}

void TheorieGreffonDifference::onBacktrack(unsigned int l)
{
    TheorieGreffonSimple::onBacktrack(l);

    for(unsigned int i = 0; i <= varIdMax; i++)
        adjacence[i].erase(adjacence[i].begin() + static_cast<int>(l), adjacence[i].end());
}

vector<AtomeDifference> TheorieGreffonDifference::getEtatCourant() const
{
    vector<AtomeDifference> etat;
    for(unsigned int sommet = 0; sommet <= varIdMax; sommet++)
        for(auto& sacNiveau : adjacence[sommet])
            for(const pair<unsigned int,int>& arete : sacNiveau)
                etat.push_back(AtomeDifference(sommet, arete.first, arete.second));
    return etat;
}