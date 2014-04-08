#ifndef FORMULE_H
#define FORMULE_H

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "Clause.h"

class Formule
{
public:
    Formule(const int variableNumber);
    Formule(const Formule& formule);
    Formule& operator= (const Formule& other);
    ~Formule();
    int size() const __attribute__((pure));
    int getNombreDeVariables() const __attribute__((pure));
    void setLiteral(int id, bool polarite, bool val);
    void setVar(int id, bool val); //id est le numéro de la variable compté à partir de 1
    bool contientClauseVide() const __attribute__((pure));
    void addClause(Clause* c);
    void addClauses(const std::unordered_set<Clause*>& c);
    void supprimerClause(Clause* c);
    bool isVide() const __attribute__((pure));
    std::unordered_set<Clause*> getClauses() const;
    ResultatEvaluation eval() const __attribute__((pure));
    void print() const;
    bool contient(const Clause* c) const;
    void supprimerSurclauses(const Clause* cl);
    bool aSousclauses(const Clause* cl) const;
    std::vector<Variable*> getVars() const;
    std::vector<Literal*> getLiterauxPositifs() const;
    std::vector<Literal*> getLiterauxNegatifs() const;
    Variable* getVar(int id) const __attribute__((pure)); //id est le numéro de la variable compté à partir de 1
    Literal* getLiteral(int id) const __attribute__((pure)); /// retourne le litéral d'identifiant i (si i > 0 cela correspond à x_i et si i < 0 à -x_(-i)
    void simplifier();
    void supprimerTautologies();

private:
    void initLits();
    void compacter();
    bool simplificationLiteralPur(int id);
    bool propagationUnitaire();
    bool eliminationLiterauxPurs();


    int V; ///Nombre de variables
    std::unordered_set<Clause*> clauses;
    std::vector<Variable*> vars;
    std::vector<Literal*> lits_pos;
    std::vector<Literal*> lits_neg;
};

#endif // FORMULE_H
