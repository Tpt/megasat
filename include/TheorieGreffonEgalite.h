#ifndef THEORIEGREFFONEGALITE_H
#define THEORIEGREFFONEGALITE_H

#include "TheorieGreffon.h"
#include "AtomeEgalite.h"
#include<unordered_map>

class TheorieGreffonEgalite : public TheorieGreffonSimple
{
public:
    TheorieGreffonEgalite();
    virtual std::vector<int> onAssignation(int id, unsigned int niveau);
    virtual void onBacktrack(unsigned int l);
    void setCorrespondanceAtomes(const std::vector<AtomeEgalite>& corr);

private:
    std::vector<AtomeEgalite> atomes;
    std::unordered_map<AtomeEgalite,int> literalPerAtome;
    std::vector<unsigned int> egalite;
    std::vector<unsigned int> poids;
    std::vector<std::vector<unsigned int>> historiqueFusions;
    std::vector<std::vector<AtomeEgalite>> differencesParNiveau;
    unsigned int varIdMax;

    void unionCC(unsigned int i, unsigned int j);
    unsigned int findCC(unsigned int i) const;
    std::vector<AtomeEgalite> construitChaineEgalites(unsigned int i) const;
    std::vector<int> testeSiUnionCCPossible(unsigned int i, unsigned int j);
};

#endif
