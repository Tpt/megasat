#ifndef AbstractDPLLSolveur_H
#define AbstractDPLLSolveur_H

#include "Solveur.h"
#include "InsatisfiableException.h"

class AbstractDPLLSolveur : public Solveur
{
public:
    AbstractDPLLSolveur(Formule &formule);
    ~AbstractDPLLSolveur();
protected:
    void assigneUneVariable();
    virtual void assigneVariable(int varId, bool val) = 0;
    std::pair<int, bool> getVariableNonAssignee() const;
    std::pair<int, bool> getVariableNonAssigneeRand() const;
    std::pair<int, bool> getVariableNonAssigneeRandMalin() const;
    std::pair<int, bool> getVariableNonAssigneeRandMOMS() const;
    std::pair<int, bool> getVariableNonAssigneeRandDLIS() const;
};

#endif
