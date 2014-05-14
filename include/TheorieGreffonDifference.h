#ifndef THEORIEGREFFONDIFFERENCE_H
#define THEORIEGREFFONDIFFERENCE_H

#include "TheorieGreffon.h"
#include "AtomeDifference.h"
#include<unordered_map>

class TheorieGreffonDifference : public TheorieGreffonSimple
{
public:
    TheorieGreffonDifference();
    virtual std::vector<int> onAssignation(int id, unsigned int niveau);
    virtual void onBacktrack(unsigned int l);
    void setCorrespondanceAtomes(const std::vector<AtomeDifference>& corr);
    std::vector<AtomeDifference> testePresenceCycleDePoidsNegatif(int depart);

private:
    std::vector<AtomeDifference> atomes;
    std::unordered_map<AtomeDifference,int> variablePerAtome;
    std::vector<std::vector<std::vector<std::pair<int,int>>>> adjacence;
    int varIdMax;
};

#endif
