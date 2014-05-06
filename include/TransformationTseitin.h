#ifndef TRANSFORMATIONTSEITIN_H
#define TRANSFORMATIONTSEITIN_H

#include "Formule.h"
#include "FormuleTseitin.h"
#include<unordered_map>

template<typename T> class TransformationTseitin
{
public:
    TransformationTseitin(FormuleTseitin<T>* formule_);
    ~TransformationTseitin();
    TransformationTseitin(const TransformationTseitin<T>& other);
    TransformationTseitin& operator=(const TransformationTseitin<T>& other);
    Formule normaliser();
    std::unordered_map<T, int> getCorrespondance() const {return correspondanceDesVariables;};

private:
    int creerCorrespondance();
    int compterVariablesAux();
    void addClausesVariable(int varCourante, T name);
    void addClausesRacine(int varCourante);
    void addClausesNon(int pere, int fils);
    void addClausesEt(int pere, int filsG, int filsD);
    void addClausesOu(int pere, int filsG, int filsD);
    void addClausesXor(int pere, int filsG, int filsD);
    void addClausesImplique(int pere, int filsG, int filsD);

    void parcours();


    FormuleTseitin<T>* formule;
    Formule* formuleNormalisee;
    int V;
    int nbrVariableAux;
    std::unordered_map<T, int> correspondanceDesVariables;
};

#include "../src/TransformationTseitin.cpp"

#endif // TRANSFORMATIONTSEITIN_H
