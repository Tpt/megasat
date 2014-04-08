#ifndef GRAPHVIZOUTPUT_H
#define GRAPHVIZOUTPUT_H

#include"Graphe.h"
#include"Formule.h"
#include<streambuf>
#include<unordered_map>

class GraphvizOutput
{
public:
    GraphvizOutput(Graphe& graphe, Formule& formule, std::unordered_map<std::string, int> correspondances, int k);
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
