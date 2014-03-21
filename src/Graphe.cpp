#include "../include/Graphe.h"

using namespace std;

Graphe::Graphe(int sommetNumber_) : sommetNumber(sommetNumber_)
{};

void Graphe::addArete(Arete arete) {
    aretes.insert(arete);
}

int Graphe::getSommetNumber() const {
    return sommetNumber;
}