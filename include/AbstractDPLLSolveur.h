#ifndef AbstractDPLLSolveur_H
#define AbstractDPLLSolveur_H

#include<unordered_map>
#include"Solveur.h"
#include"InsatisfiableException.h"

class AbstractDPLLSolveur : public Solveur
{
public:
    AbstractDPLLSolveur(Formule &formule);
    ~AbstractDPLLSolveur();
protected:
    void assigneUneVariable();
    virtual void assigneVariable(int varId, bool val) = 0;
    int getVariableNonAssignee();
};

#endif