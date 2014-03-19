#ifndef Graphe_H
#define Graphe_H

#include<unordered_set>
#include "Arete.h"

class Graphe
{
public:
    Graphe(int sommetNumber);
    void addArete(Arete arete);
private:
    int sommetNumber;
    std::unordered_set<Arete,AreteHash> aretes;
};

#endif