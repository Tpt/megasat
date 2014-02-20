#ifndef FORMULE_H
#define FORMULE_H

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"Clause.h"

class Formule
{
public:
    Formule(const Formule& formule);
    Formule(const int variableNumber);
    Formule(const int V_e, const std::vector<Variable*>& vars_e, const std::vector<Literal*>& lits_pos_e, const std::vector<Literal*>& lits_neg_e);
    ~Formule();
    int size() const;
    int getNombreDeVariables() const;
    void setLiteral(int id, bool polarite, bool val);
    void setVar(int id, bool val); //id est le numéro de la variable compté à partir de 1
    bool contientClauseVide() const;
    void addClause(Clause* c);
    void addClauses(const std::unordered_set<Clause*>& c);
    bool isVide() const;
    std::unordered_set<Clause*> getClauses() const;
    ResultatEvaluation eval() const;
    void print() const;
    bool contient(const Clause* c) const;
    void supprimerSurclauses(const Clause* cl);
    bool aSousclauses(const Clause* cl) const;
    std::vector<Variable*> getVars() const;
    std::vector<Literal*> getLiterauxPositifs() const;
    std::vector<Literal*> getLiterauxNegatifs() const;
    Variable* getVar(int id) const;
    Literal* getLiteral(int id) const; /// retourne le litéral d'identifiant i (si i > 0 cela correspond à x_i et si i < 0 à -x_(-i)
    void simplifier();

private:
    void init_lits();
    void compacter();
    bool simplificationLiteralPur(int id);
    void supprimerTautologies();
    bool propagationUnitaire();
    bool eliminationLiterauxPurs();


    int V; ///Nombre de variables
    std::unordered_set<Clause*> clauses;
    std::vector<Variable*> vars;
    std::vector<Literal*> lits_pos;
    std::vector<Literal*> lits_neg;
};

#endif // FORMULE_H
