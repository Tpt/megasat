#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<cstdlib>
#include "../include/AbstractDPLLSolveur.h"

using namespace std;

AbstractDPLLSolveur::AbstractDPLLSolveur(Formule& formule_, VariableNonAssigneeProvider& variableNonAssigneeProvider_) : Solveur(formule_), variableNonAssigneeProvider(variableNonAssigneeProvider_)
{}

AbstractDPLLSolveur::~AbstractDPLLSolveur()
{}

void AbstractDPLLSolveur::assigneUneVariable()
{
    pair<int, bool> varIdEtValeurAAssigner;
    try
    {
        varIdEtValeurAAssigner = variableNonAssigneeProvider.getVariableNonAssignee(formule);
    }
    catch(PlusDeVariablesAAssigner)
    {
        return;
    }

    int varId = varIdEtValeurAAssigner.first;
    bool val = varIdEtValeurAAssigner.second;

    Formule save = formule;

    try
    {
        assigneVariable(varId, val);
    }
    catch(InsatisfiableException)
    {
        //backtrack
        formule = save;
        assigneVariable(varId, !val);
    }
}