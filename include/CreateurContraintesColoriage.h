#ifndef CREATEURCONTRAINTESCOLORIAGE_H
#define CREATEURCONTRAINTESCOLORIAGE_H

#include "FormuleTseitin.h"
#include "Graphe.h"
#include<vector>

class CreateurContraintesColoriage
{
public:
    CreateurContraintesColoriage(Graphe &graphe, int k);
    FormuleTseitin<std::pair<int,int>>* cree() const;

private:
    FormuleTseitin<std::pair<int,int>>* creeContrainteInferieurK(int sommet) const;
    FormuleTseitin<std::pair<int,int>>* creeContrainteArete(Arete arete) const;
    inline FormuleTseitin<std::pair<int,int>>* creeVariable(int sommet, int bit) const;
    Graphe graphe;
    int k;
    int tailleCodeCouleurSommet;
};

#endif
