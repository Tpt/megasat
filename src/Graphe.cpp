#include "../include/Graphe.h"

using namespace std;

Graphe::Graphe(int sommetNumber_) : sommetNumber(sommetNumber_), aretes(unordered_set<Arete,AreteHash>())
{}

void Graphe::addArete(Arete arete)
{
    aretes.insert(arete);
}

int Graphe::getSommetNumber() const
{
    return sommetNumber;
}

unordered_set<Arete,AreteHash> Graphe::getAretes() const
{
    return aretes;
}