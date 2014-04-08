#ifndef TRANSFORMATIONTSEITIN_H
#define TRANSFORMATIONTSEITIN_H

#include "Formule.h"
#include "FormuleTseitin.h"
#include<unordered_map>

class TransformationTseitin
{
public:
    TransformationTseitin(FormuleTseitin* formule_);
    ~TransformationTseitin();
    TransformationTseitin(const TransformationTseitin& other);
    TransformationTseitin& operator=(const TransformationTseitin& other);
    Formule normaliser();
    std::unordered_map<std::string, int> getCorrespondance() const {return correspondanceDesVariables;};

private:
    int creerCorrespondance();
    int compterVariablesAux();
    void addClausesVariable(int varCourante, std::string name);
    void addClausesRacine(int varCourante);
    void addClausesNon(int pere, int fils);
    void addClausesEt(int pere, int filsG, int filsD);
    void addClausesOu(int pere, int filsG, int filsD);
    void addClausesXor(int pere, int filsG, int filsD);
    void addClausesImplique(int pere, int filsG, int filsD);

    void parcours();


    FormuleTseitin* formule;
    Formule* formuleNormalisee;
    int V;
    int nbrVariableAux;
    std::unordered_map<std::string, int> correspondanceDesVariables;
};

#endif // TRANSFORMATIONTSEITIN_H
