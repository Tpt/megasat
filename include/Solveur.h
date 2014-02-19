#ifndef Solver_H
#define Solver_H

#include<iostream>
#include"Formule.h"

class Solveur
{
public:
    Solveur(Formule Formule);
    virtual bool isSatifiable() = 0; //retourne si la formule est satifiable

protected:
    Formule formule;
};

#endif