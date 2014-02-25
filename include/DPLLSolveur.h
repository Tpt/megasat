#ifndef DPLLSolveur_H
#define DPLLSolveur_H

#include"AbstractDPLLSolveur.h"

class DPLLSolveur : public AbstractDPLLSolveur
{
public:
    DPLLSolveur(Formule &formule);
    ~DPLLSolveur();
    bool isSatifiable();
private:
    void assigneVariable(int varId, bool val);
    bool aClauseVide();
};

#endif
