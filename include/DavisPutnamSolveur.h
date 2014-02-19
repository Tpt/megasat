#ifndef DavisPutnamSolver_H
#define DavisPutnamSolver_H

#include"Solveur.h"

class DavisPutnamSolveur : public Solveur
{
public:
    DavisPutnamSolveur(Formule Formule);
    bool isSatifiable(); //retourne si la formule est satifiable
};

#endif