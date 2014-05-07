#include "../include/Terme.h"

using namespace std;

Terme::Terme() :
parametres(vector<Terme*>(0)), symbole(""), variable(-1)
{}

Terme::~Terme()
{
    //dtor
}
