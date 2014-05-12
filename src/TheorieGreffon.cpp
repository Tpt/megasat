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

vector<int> TheorieGreffonLogique::onAssignation(int id, unsigned int niveau)
{
    (void) id;
    (void) niveau;
    return vector<int>();
}

void TheorieGreffonLogique::onBacktrack(unsigned int l)
{
    (void) l;
}

void TheorieGreffonLogique::onBeginning(Formule* formule)
{
    (void) formule;
}


TheorieGreffonSimple::TheorieGreffonSimple()
{}

TheorieGreffonSimple::~TheorieGreffonSimple()
{}

void TheorieGreffonSimple::onBeginning(Formule* formule)
{
    auto vars = formule->getVars();
    valVariables = vector<ResultatEvaluation>(vars.size());
    niveauChoix = vector<int>(vars.size());
    for(unsigned int i = 0; i < vars.size(); i++)
    {
        valVariables[i] = vars[i]->eval();
    }
}

vector<int> TheorieGreffonSimple::onAssignation(int id, unsigned int niveau)
{
    int varId = abs(id) - 1;
    valVariables[varId] = (id > 0) ? VRAI : FAUX;
    niveauChoix[varId] = niveau;

    return vector<int>(0);
}

void TheorieGreffonSimple::onBacktrack(unsigned int l)
{
    for(unsigned int i = 0; i < valVariables.size(); i++)
    {
        if(niveauChoix[i] > l)
        {
            niveauChoix[i] = 0;
            valVariables[i] = INCONNU;
        }
    }
}

ResultatEvaluation TheorieGreffonSimple::getLiteralVal(int literalId)
{
    ResultatEvaluation res = valVariables[abs(literalId) - 1];
    if( res == INCONNU || literalId > 0 ) {
        return res;
    } else {
        return (res == VRAI) ? FAUX : VRAI;
    }
}