#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<cstdlib>
#include "../include/AbstractDPLLSolveur.h"

using namespace std;

AbstractDPLLSolveur::AbstractDPLLSolveur(Formule& formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_, GestionConflits& gestionConflits_) : Solveur(formule_), variableNonAssigneeProvider(variableNonAssigneeProvider_), gestionConflits(gestionConflits_)
{}

AbstractDPLLSolveur::~AbstractDPLLSolveur()
{}

void AbstractDPLLSolveur::assigneUneVariable()
{
    int literalId;
    try
    {
        literalId = variableNonAssigneeProvider.getVariableNonAssignee(formule);
    }
    catch(PlusDeVariablesAAssigner)
    {
        return;
    }

    Formule save = formule;

    try
    {
        gestionConflits.onChoix(literalId);
        assigneLiteral(literalId);
    }
    catch(InsatisfiableException)
    {
        //backtrack
        formule = save;
        gestionConflits.onChoix(literalId);
        assigneLiteral(-literalId);
    }
}
