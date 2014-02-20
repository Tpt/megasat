#ifndef Solver_H
#define Solver_H

#include<iostream>
#include"Formule.h"

class Solveur
{
public:
    Solveur(Formule& formule);
    virtual ~Solveur();
    virtual bool isSatifiable() = 0; //retourne si la formule est satifiable
    Formule getFomule() const;

protected:
    Formule& formule;
};

#endif
