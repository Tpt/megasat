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

    void addClause(Clause* c);
    void addClause(const std::vector<int>& c, int uid);
    bool contient(const Clause* c) const;
    std::unordered_set<Clause*> getClauses() const;
    Literal* getLiteral(int id) const __attribute__((pure)); /// retourne le litéral d'identifiant i (si i > 0 cela correspond à x_i et si i < 0 à -x_(-i)
    std::vector<Literal*> getLiterauxNegatifs() const;
    std::vector<Literal*> getLiterauxPositifs() const;
    int getNombreDeVariables() const __attribute__((pure));
    Variable* getVar(int id) const __attribute__((pure)); //id est le numéro de la variable compté à partir de 1
    std::vector<Variable*> getVars() const;
    bool isVide() const __attribute__((pure));
    void print() const;
    void setVar(int id, bool val); //id est le numéro de la variable compté à partir de 1
    void supprimerClause(Clause* c);
    void supprimerTautologies();

private:
    void initLits();

    int V; ///Nombre de variables
    std::unordered_set<Clause*> clauses;
    std::vector<Variable*> vars;
    std::vector<Literal*> lits_pos;
    std::vector<Literal*> lits_neg;
};

#endif // FORMULE_H
