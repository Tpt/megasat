#ifndef GestionConflits_H
#define GestionConflits_H

#include<vector>
#include "Formule.h"

class GestionConflits
{
public:
    GestionConflits(int prochainConflit = 0);
    virtual ~GestionConflits();
    virtual void onBeggining(Formule* formule);
    virtual void onDeduction(Literal* literal, int clauseUid);
    virtual void onChoix(int literalId);
    virtual void onConflit(int clauseUid);
    int getConflitsNum() const __attribute__((pure));
protected:
    int conflitsNum;
    int prochainConflit;
};

class GestionConflitsApprentissage : public GestionConflits
{
public:
    GestionConflitsApprentissage(int prochainConflit = 0);
    void onBeggining(Formule* formule);
    void onDeduction(Literal* literal, int clauseUid);
    void onChoix(int literal);
    void onConflit(int clauseUid);
private:
    void displayInterface();
    void addClause(Clause* clause);
    std::vector<std::vector<int>> clauses;
    std::vector<std::pair<int,std::vector<int>>> pileDeDeductions;
};

#endif
