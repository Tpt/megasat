#ifndef CONVERTISSEURFORMULETSEITIN_H
#define CONVERTISSEURFORMULETSEITIN_H

#include<map>
#include "Formule.h"
#include "Connecteurs.h"

class ConvertisseurFormuleTseitin
{
public:
    ConvertisseurFormuleTseitin(FormuleTseitinSimple* formuleTseitin_);
    ConvertisseurFormuleTseitin(const ConvertisseurFormuleTseitin& other);
    ConvertisseurFormuleTseitin& operator= (const ConvertisseurFormuleTseitin& other);
    ~ConvertisseurFormuleTseitin();
    Formule convertir();

private:
    int creerCorrespondance();
    void decomposerEt(const FormuleTseitinSimple& f);
    void decomposerOu(const FormuleTseitinSimple& f, std::unordered_set<Literal*>& clauseEnConstruction);


    FormuleTseitinSimple* formuleTseitin;
    Formule* formuleNormalisee;
    int V;
    std::map<std::string, int> correspondanceDesVariables;
};

#endif // CONVERTISSEURFORMULETSEITIN_H
