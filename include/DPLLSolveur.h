#ifndef DPLLSolveur_H
#define DPLLSolveur_H

#include "AbstractDPLLSolveur.h"

class DPLLSolveur : public AbstractDPLLSolveur
{
public:
    DPLLSolveur(Formule& formule, VariableNonAssigneeProvider& variableNonAssigneeProvider, GestionConflits& gestionConflits_);
    ~DPLLSolveur();
    bool isSatifiable();
private:
    void assigneVariable(int varId, bool val);
    bool aClauseVide();
    void simplifier();
    void compacter();
    bool eliminationLiterauxPurs();
    bool propagationUnitaire();
    bool simplificationLiteralPur(int id);
};

#endif
