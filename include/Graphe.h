#ifndef Graphe_H
#define Graphe_H

#include "std.h"
#include "Arete.h"
#include<unordered_set>

class Graphe
{
public:
    Graphe(int sommetNumber);
    void addArete(Arete arete);
    int getSommetNumber() const __attribute__((pure));
    std::unordered_set<Arete> getAretes() const;
private:
    int sommetNumber;
    std::unordered_set<Arete> aretes;
};

#endif
