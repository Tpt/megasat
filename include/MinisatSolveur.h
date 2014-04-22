#ifndef MinisatSolveur_H
#define MinisatSolveur_H

#include "Solveur.h"

class MinisatSolveur : public Solveur
{
public:
    MinisatSolveur(Formule& formule);
protected:
    bool isSatifiable();
};

#endif
