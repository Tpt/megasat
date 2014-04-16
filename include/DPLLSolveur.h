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
    void assigneLiteral(int literalId);
    void verifierAPasClauseVide();
    void simplifier();
    void compacter();
    bool eliminationLiterauxPurs();
    bool propagationUnitaire();
    bool simplificationUnitaire(Clause* clause);
    bool simplificationLiteralPur(int id);
};

#endif