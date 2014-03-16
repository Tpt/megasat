#include "../include/ConvertisseurFormuleTseitin.h"
#include<stack>

using namespace std;

ConvertisseurFormuleTseitin::ConvertisseurFormuleTseitin(FormuleTseitinSimple* formuleTseitin_) :
formuleTseitin(formuleTseitin_), formuleNormalisee(nullptr), V(0), correspondanceDesVariables(map<string,int>())
{
    V=creerCorrespondance();

    formuleNormalisee = new Formule(V);
}

ConvertisseurFormuleTseitin::ConvertisseurFormuleTseitin(const ConvertisseurFormuleTseitin& other) :
formuleTseitin(new FormuleTseitinSimple(*other.formuleTseitin)), formuleNormalisee(new Formule(*other.formuleNormalisee)), V(other.V), correspondanceDesVariables(other.correspondanceDesVariables)
{}

ConvertisseurFormuleTseitin& ConvertisseurFormuleTseitin::operator= (const ConvertisseurFormuleTseitin& other)
{
    ConvertisseurFormuleTseitin Temp(other);

    swap(Temp.formuleTseitin, this->formuleTseitin);
    swap(Temp.formuleNormalisee, this->formuleNormalisee);
    swap(Temp.correspondanceDesVariables, this->correspondanceDesVariables);

    return *this;
}

ConvertisseurFormuleTseitin::~ConvertisseurFormuleTseitin()
{
    delete formuleTseitin;
    delete formuleNormalisee;
}

int ConvertisseurFormuleTseitin::creerCorrespondance() ///Renvoie le nombre de variables
{
    int Uid=1;
    stack<FormuleTseitinSimple> pile;
    FormuleTseitinSimple w;

    pile.push(*formuleTseitin);

    while(!pile.empty())
    {
        w=pile.top();
        pile.pop();
        if(w.getType()==FormuleTseitinSimple::VARIABLE)
        {
            if(correspondanceDesVariables.count(w.getName())==0)
            {
                correspondanceDesVariables[w.getName()]=Uid;
                ++Uid;
            }
        }
        else if(w.getArite()==1)
        {
            pile.push(w.getOperande());
        }
        else if(w.getArite()==2)
        {
            pile.push(w.getOperandeG());
            pile.push(w.getOperandeD());
        }
    }

    return Uid-1;
}

Formule ConvertisseurFormuleTseitin::ConvertisseurFormuleTseitin::convertir()
{
    *formuleTseitin = formuleTseitin->transformationDeMorgan();
    decomposerEt(*formuleTseitin);
    return *formuleNormalisee;
}

void ConvertisseurFormuleTseitin::decomposerEt(const FormuleTseitinSimple& f)
{
    if(f.getType()==FormuleTseitinSimple::ET)
    {
        decomposerEt(f.getOperandeD());
        decomposerEt(f.getOperandeG());
    }
    else
    {
        unordered_set<Literal*> clauseEnConstruction;
        decomposerOu(f, clauseEnConstruction);
        Clause* c = new Clause(V);
        c->addLiteraux(clauseEnConstruction);
        formuleNormalisee->addClause(c);
    }
}

void ConvertisseurFormuleTseitin::decomposerOu(const FormuleTseitinSimple& f, unordered_set<Literal*>& clauseEnConstruction)
{
    if(f.getType()==FormuleTseitinSimple::OU)
    {
        decomposerOu(f.getOperandeD(), clauseEnConstruction);
        decomposerOu(f.getOperandeG(), clauseEnConstruction);
    }
    else if(f.getType()==FormuleTseitinSimple::VARIABLE)
    {
        clauseEnConstruction.insert(formuleNormalisee->getLiteral(correspondanceDesVariables[f.getName()]));
    }
    else/// donc if(f->getType()==FormuleTseitinSimple::NON)
    {
        clauseEnConstruction.insert(formuleNormalisee->getLiteral(correspondanceDesVariables[f.getOperande().getName()]));
    }
}
