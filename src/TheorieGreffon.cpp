#include "../include/TheorieGreffon.h"
#include "../include/InsatisfiableException.h"

using namespace std;

TheorieGreffon::TheorieGreffon()
{}

TheorieGreffon::~TheorieGreffon()
{}

vector<int> TheorieGreffon::getTPropagations(unsigned int niveau)
{
    return vector<int>(0);
}

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

bool TheorieGreffonLogique::avecEliminationLiterauxPurs() const
{
    return true;
}


TheorieGreffonSimple::TheorieGreffonSimple()
{}

TheorieGreffonSimple::~TheorieGreffonSimple()
{}

void TheorieGreffonSimple::onBeginning(Formule* formule)
{
    auto vars = formule->getVars();
    valVariables = vector<ResultatEvaluation>(vars.size(), INCONNU);
    niveauChoix = vector<unsigned int>(vars.size());
    for(unsigned int i = 0; i < vars.size(); i++)
    {
        ResultatEvaluation eval = vars[i]->eval();
        if(eval != INCONNU)
        {
            vector<int> clauseAAjouter = onAssignation( (eval == VRAI) ? i + 1 : -i - 1, 0 );
            if(!clauseAAjouter.empty())
                throw InsatisfiableException();
        }
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
        if(niveauChoix[i] >= l)
        {
            niveauChoix[i] = 0;
            valVariables[i] = INCONNU;
        }
    }
}

bool TheorieGreffonSimple::avecEliminationLiterauxPurs() const
{
    return false;
}
