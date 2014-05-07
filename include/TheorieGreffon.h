#ifndef TheorieGreffon_H
#define TheorieGreffon_H

#include<vector>

class TheorieGreffon //Interface
{
public:
    TheorieGreffon();
    virtual ~TheorieGreffon();
    virtual std::vector<int> onAssignation(int id, int niveau) = 0; //Si fail, renvoie avec clause à apprendre
    virtual void onBacktrack(int l) = 0; //Remonter au niveau l

protected:
};

class TheorieGreffonLogique : public TheorieGreffon //Greffon pour les formule logique : chaque litéral de la Formule se représente lui même
{
public:
    TheorieGreffonLogique();
    virtual ~TheorieGreffonLogique();
    virtual std::vector<int> onAssignation(int id, int niveau);
    virtual void onBacktrack(int l);

protected:
};

#endif
