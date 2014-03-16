#include "../include/TransformationTseitin.h"
#include<stack>

using namespace std;

TransformationTseitin::TransformationTseitin(FormuleTseitinSimple* formule_) :
formule(formule_), formuleNormalisee(nullptr), V(0), correspondanceDesVariables(map<string,int>())
{
    V=creerCorrespondance();
    nbrVariableAux=compterVariablesAux();

    formuleNormalisee = new Formule(V+nbrVariableAux);
}

TransformationTseitin::TransformationTseitin(const TransformationTseitin& other) :
formule(new FormuleTseitinSimple(*other.formule)), formuleNormalisee(new Formule(*other.formuleNormalisee)), V(other.V), correspondanceDesVariables(other.correspondanceDesVariables)
{}

TransformationTseitin& TransformationTseitin::operator= (const TransformationTseitin& other)
{
    TransformationTseitin Temp(other);

    swap(Temp.formule, this->formule);
    swap(Temp.formuleNormalisee, this->formuleNormalisee);
    swap(Temp.correspondanceDesVariables, this->correspondanceDesVariables);

    return *this;
}

TransformationTseitin::~TransformationTseitin()
{
    delete formule;
    delete formuleNormalisee;
}

int TransformationTseitin::creerCorrespondance() ///Renvoie le nombre de variables
{
    int Uid=1;
    stack<FormuleTseitinSimple> pile;
    FormuleTseitinSimple w;

    pile.push(*formule);

    while(!pile.empty())
    {
        w=pile.top();
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

        pile.pop();
    }

    return Uid-1;
}

int TransformationTseitin::compterVariablesAux() ///Renvoie le nombre de variables auxilliaires à créer.
{
    int count=V;
    stack<FormuleTseitinSimple> pile;
    FormuleTseitinSimple w;

    pile.push(*formule);

    while(!pile.empty())
    {
        w=pile.top();
        if(w.getType()==FormuleTseitinSimple::VARIABLE)
        {
            count--;
        }
        else if(w.getArite()==1)
        {
            count++;
            pile.push(w.getOperande());
        }
        else if(w.getArite()==2)
        {
            count++;
            pile.push(w.getOperandeG());
            pile.push(w.getOperandeD());
        }

        pile.pop();
    }

    return count;
}
