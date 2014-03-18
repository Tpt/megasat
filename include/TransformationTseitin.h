#ifndef TRANSFORMATIONTSEITIN_H
#define TRANSFORMATIONTSEITIN_H

#include "Formule.h"
#include "Connecteurs.h"
#include<map>

class TransformationTseitin
{
public:
    TransformationTseitin(FormuleTseitinSimple* formule_);
    ~TransformationTseitin();
    TransformationTseitin(const TransformationTseitin& other);
    TransformationTseitin& operator=(const TransformationTseitin& other);
    Formule normaliser();

private:
    int creerCorrespondance();
    int compterVariablesAux();
    void addClausesVariable(int varCourrante, std::string name);
    void addClausesNon(int pere, int fils);
    void addClausesEt(int pere, int filsG, int filsD);
    void addClausesOu(int pere, int filsG, int filsD);
    void parcours();


    FormuleTseitinSimple* formule;
    Formule* formuleNormalisee;
    int V;
    int nbrVariableAux;
    std::map<std::string, int> correspondanceDesVariables;
};

#endif // TRANSFORMATIONTSEITIN_H