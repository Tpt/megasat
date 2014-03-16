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

private:
    int creerCorrespondance();
    int compterVariablesAux();

    FormuleTseitinSimple* formule;
    Formule* formuleNormalisee;
    int V;
    int nbrVariableAux;
    std::map<std::string, int> correspondanceDesVariables;
};

#endif // TRANSFORMATIONTSEITIN_H
