#ifndef GRAPHVIZOUTPUT_H
#define GRAPHVIZOUTPUT_H

#include"Graphe.h"
#include"Formule.h"
#include<streambuf>
#include<map>

class GraphvizOutput
{
public:
    GraphvizOutput(Graphe& graphe, Formule& formule, std::map<std::string, int> correspondances, int k);
    void affiche(std::streambuf* sortie);
private:
    int getCouleur(int sommet);
    Graphe graphe;
    Formule formule;
    int k;
    int tailleCodeCouleurSommet;
    std::map<std::string, int> correspondances;
};

#endif
