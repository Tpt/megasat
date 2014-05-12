#ifndef TheorieGreffon_H
#define TheorieGreffon_H

#include<vector>
#include "Formule.h"

class TheorieGreffon //Interface
{
public:
    TheorieGreffon();
    virtual ~TheorieGreffon();
    virtual std::vector<int> onAssignation(int id, unsigned int niveau) = 0; //Si fail, renvoie clause à apprendre
    virtual void onBacktrack(unsigned int l) = 0; //Remonter au niveau l
    virtual void onBeginning(Formule* formule) = 0;

protected:
};

class TheorieGreffonLogique : public TheorieGreffon //Greffon pour les formule logique : chaque litéral de la Formule se représente lui même
{
public:
    TheorieGreffonLogique();
    virtual ~TheorieGreffonLogique();
    virtual std::vector<int> onAssignation(int id, unsigned int niveau);
    virtual void onBacktrack(unsigned int l);
    virtual void onBeginning(Formule* formule);

protected:
};

#endif
