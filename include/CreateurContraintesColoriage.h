#ifndef CREATEURCONTRAINTESCOLORIAGE_H
#define CREATEURCONTRAINTESCOLORIAGE_H

#include "FormuleTseitin.h"
#include "Graphe.h"
#include<vector>

class CreateurContraintesColoriage
{
public:
    CreateurContraintesColoriage(Graphe &graphe, int k);
    FormuleTseitin* cree() const;

private:
    FormuleTseitin* creeContrainteInferieurK(int sommet) const;
    FormuleTseitin* creeContrainteArete(Arete arete) const;
    FormuleTseitin* creeVariable(int sommet, int bit) const;
    Graphe graphe;
    int k;
    int tailleCodeCouleurSommet;
};

#endif
