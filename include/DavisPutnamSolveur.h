#ifndef DavisPutnamSolver_H
#define DavisPutnamSolver_H

#include"Solveur.h"

class DavisPutnamSolveur : public Solveur
{
public:
    DavisPutnamSolveur(Formule Formule);
    bool estSatifiable(); //retourne si la formule est satifiable
private:
    Formule* resoudreSeau(const Formule* seau, int id) const;
};

#endif