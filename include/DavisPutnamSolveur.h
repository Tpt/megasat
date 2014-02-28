#ifndef DavisPutnamSolver_H
#define DavisPutnamSolver_H

#include "Solveur.h"

class DavisPutnamSolveur : public Solveur
{
public:
    DavisPutnamSolveur(Formule &formule);
    ~DavisPutnamSolveur();
    bool isSatifiable(); //retourne si la formule est satifiable

private:
    std::unordered_set<Clause*> resoudreSeau(const std::unordered_set<Clause*>& seau, int id) const;
    void fusionner(const std::unordered_set<Clause*>& e, std::vector<std::unordered_set<Clause*> >& seaux) const;
    void chercherAssignation(std::unordered_set<Clause*>& f, int id);
    Clause* resolution(const Clause* c1, Clause* c2, const int id) const;
    bool contient(const std::unordered_set<Clause*> seau, const Clause* clause) const;
    bool aSousclauses(const std::unordered_set<Clause*> seau, const Clause* cl) const;
    ResultatEvaluation eval(const std::unordered_set<Clause*>& seau) const;
};

#endif
