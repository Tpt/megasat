#ifndef CFORMULE_H
#define CFORMULE_H

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"CClause.h"

class CFormule
{
    public:
    CFormule();
    CFormule(std::string filename);
    ~CFormule();
    CFormule(const CFormule& other);
    CFormule(const int V_e, const int C_e, const std::vector<CVariable*>& vars_e, const std::vector<CLiteral*>& lits_pos_e, const std::vector<CLiteral*>& lits_neg_e);
    int size() const;
    void solve();
    bool isThereClauseVide() const;
    void addClause(CClause* c);
    void addClauses(const std::unordered_set<CClause*>& c);
    bool isVide() const;
    std::unordered_set<CClause*> getClauses() const;
    int eval() const;
    void fusionner(const CFormule* e, std::vector<CFormule*> seaux) const;
    void print() const;
    bool contient(const CClause* c) const;
    void supprimer_surclauses(const CClause* cl);
    bool aSousclauses(const CClause* cl) const;
    std::vector<CVariable*> getVars() const;
    CVariable* getVar(int id) const;

    private:
    CClause* resolution(const CClause* c1, CClause* c2, const int id) const;
    CFormule* resoudre_seau(const CFormule* seau, int id) const;
    void init_lits();
    void chercher_assignation(CFormule* f, int id);


    int V; ///Nombre de variables
    int C; ///Nombre de clauses
    std::unordered_set<CClause*> clauses;
    std::vector<CVariable*> vars;
    std::vector<CLiteral*> lits_pos;
    std::vector<CLiteral*> lits_neg;
};

#endif // CFORMULE_H
