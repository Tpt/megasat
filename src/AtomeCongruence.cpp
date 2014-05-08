#include "../include/AtomeCongruence.h"

using namespace std;

AtomeCongruence::AtomeCongruence() : gauche(Terme()), droite(Terme())
{}

AtomeCongruence::AtomeCongruence(Terme gauche_, Terme droite_) : gauche(gauche_), droite(droite_)
{}

AtomeCongruence::~AtomeCongruence()
{}
