#ifndef DavisPutnamSolver_H
#define DavisPutnamSolver_H

#include"Solveur.h"

class DavisPutnamSolveur : public Solveur
{
public:
    DavisPutnamSolveur(Formule &formule);
    bool isSatifiable(); //retourne si la formule est satifiable

private:
    Formule* resoudreSeau(const Formule* seau, int id) const;
    void fusionner(const Formule* e, std::vector<Formule*> seaux) const;
    void chercherAssignation(Formule* f, int id);
    Clause* resolution(const Clause* c1, Clause* c2, const int id) const;
};

#endif
