#include "../include/TransformationTseitin.h"
#include<stack>

using namespace std;

template<typename T> TransformationTseitin<T>::TransformationTseitin(FormuleTseitin<T>* formule_) :
formule(formule_), formuleNormalisee(nullptr), V(0), nbrVariableAux(0), correspondanceDesVariables(unordered_map<T,int>())
{
    V = creerCorrespondance();
    nbrVariableAux = compterVariablesAux();

    formuleNormalisee = new Formule(V + nbrVariableAux);
}

template<typename T> TransformationTseitin<T>::TransformationTseitin(const TransformationTseitin& other) :
formule(new FormuleTseitin<T>(*other.formule)), formuleNormalisee(new Formule(*other.formuleNormalisee)), V(other.V), nbrVariableAux(other.nbrVariableAux), correspondanceDesVariables(other.correspondanceDesVariables)
{}

template<typename T> TransformationTseitin<T>& TransformationTseitin<T>::operator= (const TransformationTseitin& other)
{
    TransformationTseitin Temp(other);

    swap(Temp.formule, this->formule);
    swap(Temp.formuleNormalisee, this->formuleNormalisee);
    swap(Temp.correspondanceDesVariables, this->correspondanceDesVariables);
    swap(Temp.nbrVariableAux, this->nbrVariableAux);
    swap(Temp.V, this->V);

    return *this;
}

template<typename T> TransformationTseitin<T>::~TransformationTseitin()
{
    delete formuleNormalisee;
}

template<typename T> int TransformationTseitin<T>::creerCorrespondance() ///Renvoie le nombre de variables
{
    int Uid = 1;
    stack<FormuleTseitin<T>> pile;
    FormuleTseitin<T> w;

    pile.push(*formule);

    while(!pile.empty())
    {
        w = pile.top();
        pile.pop();
        if(w.getType() == FormuleTseitin<T>::VARIABLE)
        {
            if(correspondanceDesVariables.count(w.getName()) == 0)
            {
                correspondanceDesVariables[w.getName()] = Uid;
                ++Uid;
            }
        }
        else if(w.getArite() == 1)
        {
            pile.push(w.getOperande());
        }
        else if(w.getArite() == 2)
        {
            pile.push(w.getOperandeG());
            pile.push(w.getOperandeD());
        }
    }

    return Uid - 1;
}

template<typename T> int TransformationTseitin<T>::compterVariablesAux() ///Renvoie le nombre de variables auxilliaires à créer.
{
    int count = 1;
    stack<FormuleTseitin<T>> pile;
    FormuleTseitin<T> w;

    pile.push(*formule);

    while(!pile.empty())
    {
        w = pile.top();
        pile.pop();
        if(w.getType() == FormuleTseitin<T>::VARIABLE)
        {
            continue;
        }
        else if(w.getArite() == 1)
        {
            count++;
            pile.push(w.getOperande());
        }
        else if(w.getArite() == 2)
        {
            count += 2;
            pile.push(w.getOperandeD());
            pile.push(w.getOperandeG());
        }

    }

    return count;
}

template<typename T> Formule TransformationTseitin<T>::normaliser()
{
    parcours();
    return *formuleNormalisee;
}

template<typename T> void TransformationTseitin<T>::parcours()
{
    stack<pair<FormuleTseitin<T>,int>> pile;
    int varCourante = V + 1;

    addClausesRacine(varCourante);

    pile.push(pair<FormuleTseitin<T>,int>(*formule, varCourante));

    while(!pile.empty())
    {
        int v = pile.top().second;
        FormuleTseitin<T> w = pile.top().first;
        
        pile.pop();
        if(w.getType() == FormuleTseitin<T>::VARIABLE)
        {
            addClausesVariable(v, w.getName());
        }
        else if(w.getType() == FormuleTseitin<T>::NON)
        {
            ++varCourante;
            addClausesNon(v,varCourante);
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperande(),varCourante));
        }
        else if(w.getType() == FormuleTseitin<T>::ET)
        {
            ++varCourante;
            addClausesEt(v,varCourante, varCourante+1);
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperandeD(),varCourante+1));
            ++varCourante;
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperandeG(),varCourante-1));
        }
        else if(w.getType() == FormuleTseitin<T>::OU)
        {
            ++varCourante;
            addClausesOu(v,varCourante, varCourante+1);
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperandeD(),varCourante+1));
            ++varCourante;
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperandeG(),varCourante-1));
        }
        else if(w.getType() == FormuleTseitin<T>::IMPLIQUE)
        {
            ++varCourante;
            addClausesImplique(v,varCourante, varCourante+1);
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperandeD(),varCourante+1));
            ++varCourante;
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperandeG(),varCourante-1));
        }
        else if(w.getType() == FormuleTseitin<T>::XOR)
        {
            ++varCourante;
            addClausesXor(v,varCourante, varCourante+1);
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperandeG(),varCourante+1));
            ++varCourante;
            pile.push(pair<FormuleTseitin<T>,int>(w.getOperandeD(),varCourante-1));
        }
    }
}

template<typename T> void TransformationTseitin<T>::addClausesRacine(int varCourante)
{
    Clause* c = new Clause(V+nbrVariableAux);
    c->addLiteral(formuleNormalisee->getLiteral(varCourante));
    formuleNormalisee->addClause(c);
}

template<typename T> void TransformationTseitin<T>::addClausesVariable(int varCourante, T name)
{
    Clause* c1 = new Clause(V+nbrVariableAux);
    Clause* c2 = new Clause(V+nbrVariableAux);

    c1->addLiteral(formuleNormalisee->getLiteral(-varCourante));
    c1->addLiteral(formuleNormalisee->getLiteral(correspondanceDesVariables[name]));
    c2->addLiteral(formuleNormalisee->getLiteral(varCourante));
    c2->addLiteral(formuleNormalisee->getLiteral(-correspondanceDesVariables[name]));

    formuleNormalisee->addClause(c1);
    formuleNormalisee->addClause(c2);
}

template<typename T> void TransformationTseitin<T>::addClausesNon(int pere, int fils)
{
    Clause* c1 = new Clause(V+nbrVariableAux);
    Clause* c2 = new Clause(V+nbrVariableAux);

    c1->addLiteral(formuleNormalisee->getLiteral(-pere));
    c1->addLiteral(formuleNormalisee->getLiteral(-fils));
    c2->addLiteral(formuleNormalisee->getLiteral(pere));
    c2->addLiteral(formuleNormalisee->getLiteral(fils));

    formuleNormalisee->addClause(c1);
    formuleNormalisee->addClause(c2);
}

template<typename T> void TransformationTseitin<T>::addClausesEt(int pere, int filsG, int filsD)
{
    Clause* c1 = new Clause(V+nbrVariableAux);
    Clause* c2 = new Clause(V+nbrVariableAux);
    Clause* c3 = new Clause(V+nbrVariableAux);

    c1->addLiteral(formuleNormalisee->getLiteral(-pere));
    c1->addLiteral(formuleNormalisee->getLiteral(filsG));
    c2->addLiteral(formuleNormalisee->getLiteral(-pere));
    c2->addLiteral(formuleNormalisee->getLiteral(filsD));
    c3->addLiteral(formuleNormalisee->getLiteral(pere));
    c3->addLiteral(formuleNormalisee->getLiteral(-filsD));
    c3->addLiteral(formuleNormalisee->getLiteral(-filsG));

    formuleNormalisee->addClause(c1);
    formuleNormalisee->addClause(c2);
    formuleNormalisee->addClause(c3);
}

template<typename T> void TransformationTseitin<T>::addClausesOu(int pere, int filsG, int filsD)
{
    Clause* c1 = new Clause(V+nbrVariableAux);
    Clause* c2 = new Clause(V+nbrVariableAux);
    Clause* c3 = new Clause(V+nbrVariableAux);

    c1->addLiteral(formuleNormalisee->getLiteral(pere));
    c1->addLiteral(formuleNormalisee->getLiteral(-filsG));
    c2->addLiteral(formuleNormalisee->getLiteral(pere));
    c2->addLiteral(formuleNormalisee->getLiteral(-filsD));
    c3->addLiteral(formuleNormalisee->getLiteral(-pere));
    c3->addLiteral(formuleNormalisee->getLiteral(filsD));
    c3->addLiteral(formuleNormalisee->getLiteral(filsG));

    formuleNormalisee->addClause(c1);
    formuleNormalisee->addClause(c2);
    formuleNormalisee->addClause(c3);
}

template<typename T> void TransformationTseitin<T>::addClausesXor(int pere, int filsG, int filsD)
{
    Clause* c1 = new Clause(V+nbrVariableAux);
    Clause* c2 = new Clause(V+nbrVariableAux);
    Clause* c3 = new Clause(V+nbrVariableAux);
    Clause* c4 = new Clause(V+nbrVariableAux);

    c1->addLiteral(formuleNormalisee->getLiteral(-pere));
    c1->addLiteral(formuleNormalisee->getLiteral(filsG));
    c1->addLiteral(formuleNormalisee->getLiteral(filsD));

    c2->addLiteral(formuleNormalisee->getLiteral(pere));
    c2->addLiteral(formuleNormalisee->getLiteral(-filsG));
    c2->addLiteral(formuleNormalisee->getLiteral(filsD));

    c3->addLiteral(formuleNormalisee->getLiteral(pere));
    c3->addLiteral(formuleNormalisee->getLiteral(filsD));
    c3->addLiteral(formuleNormalisee->getLiteral(-filsG));

    c4->addLiteral(formuleNormalisee->getLiteral(-pere));
    c4->addLiteral(formuleNormalisee->getLiteral(-filsD));
    c4->addLiteral(formuleNormalisee->getLiteral(-filsG));

    formuleNormalisee->addClause(c1);
    formuleNormalisee->addClause(c2);
    formuleNormalisee->addClause(c3);
    formuleNormalisee->addClause(c4);
}

template<typename T> void TransformationTseitin<T>::addClausesImplique(int pere, int filsG, int filsD)
{
    Clause* c1 = new Clause(V+nbrVariableAux);
    Clause* c2 = new Clause(V+nbrVariableAux);
    Clause* c3 = new Clause(V+nbrVariableAux);

    c1->addLiteral(formuleNormalisee->getLiteral(-pere));
    c1->addLiteral(formuleNormalisee->getLiteral(-filsG));
    c1->addLiteral(formuleNormalisee->getLiteral(filsD));

    c2->addLiteral(formuleNormalisee->getLiteral(pere));
    c2->addLiteral(formuleNormalisee->getLiteral(filsG));

    c3->addLiteral(formuleNormalisee->getLiteral(pere));
    c3->addLiteral(formuleNormalisee->getLiteral(-filsD));

    formuleNormalisee->addClause(c1);
    formuleNormalisee->addClause(c2);
    formuleNormalisee->addClause(c3);
}
