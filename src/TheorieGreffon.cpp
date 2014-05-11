#include "../include/TheorieGreffon.h"

using namespace std;

TheorieGreffon::TheorieGreffon()
{}

TheorieGreffon::~TheorieGreffon()
{}

TheorieGreffonLogique::TheorieGreffonLogique()
{}

TheorieGreffonLogique::~TheorieGreffonLogique()
{}

vector<int> TheorieGreffonLogique::onAssignation(int id, int niveau)
{
    (void) id;
    (void) niveau;
    return vector<int>();
}

void TheorieGreffonLogique::onBacktrack(int l)
{
    (void) l;
}

void TheorieGreffonLogique::onBeginning(Formule* formule)
{
    (void) formule;
}
