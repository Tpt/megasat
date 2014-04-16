#ifndef GraphvizConflitOutput_H
#define GraphvizConflitOutput_H

#include"Graphe.h"
#include"Formule.h"
#include<streambuf>
#include<unordered_map>

class GraphvizConflitOutput
{
public:
    GraphvizConflitOutput(std::vector<std::pair<int,std::vector<int>>>& pile);
    void affiche(std::streambuf* sortie);
    void affiche(std::string& fichierSortie);
private:
    std::vector<std::pair<int,std::vector<int>>> pile;
};

#endif
