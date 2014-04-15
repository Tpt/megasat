#ifndef GraphvizColoriageOutput_H
#define GraphvizColoriageOutput_H

#include"Graphe.h"
#include"Formule.h"
#include<streambuf>
#include<unordered_map>

class GraphvizColoriageOutput
{
public:
    GraphvizColoriageOutput(Graphe& graphe, Formule& formule, const std::unordered_map<std::string, int>& correspondances, int k);
    void affiche(std::streambuf* sortie, bool avecColoriage = false);
private:
    int getCouleur(int sommet);
    Graphe graphe;
    Formule formule;
    int k;
    int tailleCodeCouleurSommet;
    std::unordered_map<std::string, int> correspondances;
};

#endif
