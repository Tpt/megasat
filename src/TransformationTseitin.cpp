#include "../include/TransformationTseitin.h"
#include<stack>

using namespace std;

TransformationTseitin::TransformationTseitin(FormuleTseitin* formule_) :
formule(formule_), formuleNormalisee(nullptr), V(0), nbrVariableAux(0), correspondanceDesVariables(map<string,int>())
{
    V = creerCorrespondance();
    nbrVariableAux = compterVariablesAux();

    formuleNormalisee = new Formule(V + nbrVariableAux);
}

TransformationTseitin::TransformationTseitin(const TransformationTseitin& other) :
formule(new FormuleTseitin(*other.formule)), formuleNormalisee(new Formule(*other.formuleNormalisee)), V(other.V), nbrVariableAux(other.nbrVariableAux), correspondanceDesVariables(other.correspondanceDesVariables)
{}

TransformationTseitin& TransformationTseitin::operator= (const TransformationTseitin& other)
{
    TransformationTseitin Temp(other);

    swap(Temp.formule, this->formule);
    swap(Temp.formuleNormalisee, this->formuleNormalisee);
    swap(Temp.correspondanceDesVariables, this->correspondanceDesVariables);
    swap(Temp.nbrVariableAux, this->nbrVariableAux);
    swap(Temp.V, this->V);

    return *this;
}

TransformationTseitin::~TransformationTseitin()
{
    delete formule;
    delete formuleNormalisee;
}

int TransformationTseitin::creerCorrespondance() ///Renvoie le nombre de variables
{
    int Uid = 1;
    stack<FormuleTseitin> pile;
    FormuleTseitin w;

    pile.push(*formule);

    while(!pile.empty())
    {
        w = pile.top();
        pile.pop();
        if(w.getType() == FormuleTseitin::VARIABLE)
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

int TransformationTseitin::compterVariablesAux() ///Renvoie le nombre de variables auxilliaires à créer.
{
    int count = 1;
    stack<FormuleTseitin> pile;
    FormuleTseitin w;

    pile.push(*formule);

    while(!pile.empty())
    {
        w = pile.top();
        pile.pop();
        if(w.getType() == FormuleTseitin::VARIABLE)
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

Formule TransformationTseitin::normaliser()
{
    parcours();
    return *formuleNormalisee;
}

void TransformationTseitin::parcours()
{
    stack<pair<FormuleTseitin,int>> pile;
    int varCourante = V + 1;
    FormuleTseitin w;
    int v;

    addClausesRacine(varCourante);

    pile.push(pair<FormuleTseitin,int>(*formule, varCourante));

    while(!pile.empty())
    {
        v = pile.top().second;
        w = pile.top().first;
        
        pile.pop();
        if(w.getType()==FormuleTseitin::VARIABLE)
        {
            addClausesVariable(v, w.getName());
        }
        else if(w.getType()==FormuleTseitin::NON)
        {
            ++varCourante;
            addClausesNon(v,varCourante);
            pile.push(pair<FormuleTseitin,int>(w.getOperande(),varCourante));
        }
        else if(w.getType()==FormuleTseitin::ET)
        {
            ++varCourante;
            addClausesEt(v,varCourante, varCourante+1);
            pile.push(pair<FormuleTseitin,int>(w.getOperandeD(),varCourante+1));
            ++varCourante;
            pile.push(pair<FormuleTseitin,int>(w.getOperandeG(),varCourante-1));
        }
        else if(w.getType()==FormuleTseitin::OU)
        {
            ++varCourante;
            addClausesOu(v,varCourante, varCourante+1);
            pile.push(pair<FormuleTseitin,int>(w.getOperandeD(),varCourante+1));
            ++varCourante;
            pile.push(pair<FormuleTseitin,int>(w.getOperandeG(),varCourante-1));
        }
        else if(w.getType()==FormuleTseitin::IMPLIQUE)
        {
            ++varCourante;
            addClausesImplique(v,varCourante, varCourante+1);
            pile.push(pair<FormuleTseitin,int>(w.getOperandeD(),varCourante+1));
            ++varCourante;
            pile.push(pair<FormuleTseitin,int>(w.getOperandeG(),varCourante-1));
        }
        else if(w.getType()==FormuleTseitin::XOR)
        {
            ++varCourante;
            addClausesXor(v,varCourante, varCourante+1);
            pile.push(pair<FormuleTseitin,int>(w.getOperandeG(),varCourante+1));
            ++varCourante;
            pile.push(pair<FormuleTseitin,int>(w.getOperandeD(),varCourante-1));
        }
    }
}

void TransformationTseitin::addClausesRacine(int varCourante)
{
    Clause c(V+nbrVariableAux);
    c.addLiteral(formuleNormalisee->getLiteral(varCourante));
    formuleNormalisee->addClause(new Clause(c));
}

void TransformationTseitin::addClausesVariable(int varCourante, string name)
{
    Clause c1(V+nbrVariableAux);
    Clause c2(V+nbrVariableAux);

    c1.addLiteral(formuleNormalisee->getLiteral(-varCourante));
    c1.addLiteral(formuleNormalisee->getLiteral(correspondanceDesVariables[name]));
    c2.addLiteral(formuleNormalisee->getLiteral(varCourante));
    c2.addLiteral(formuleNormalisee->getLiteral(-correspondanceDesVariables[name]));

    formuleNormalisee->addClause(new Clause(c1));
    formuleNormalisee->addClause(new Clause(c2));
}

void TransformationTseitin::addClausesNon(int pere, int fils)
{
    Clause c1(V+nbrVariableAux);
    Clause c2(V+nbrVariableAux);

    c1.addLiteral(formuleNormalisee->getLiteral(-pere));
    c1.addLiteral(formuleNormalisee->getLiteral(-fils));
    c2.addLiteral(formuleNormalisee->getLiteral(pere));
    c2.addLiteral(formuleNormalisee->getLiteral(fils));

    formuleNormalisee->addClause(new Clause(c1));
    formuleNormalisee->addClause(new Clause(c2));
}

void TransformationTseitin::addClausesEt(int pere, int filsG, int filsD)
{
    Clause c1(V+nbrVariableAux);
    Clause c2(V+nbrVariableAux);
    Clause c3(V+nbrVariableAux);

    c1.addLiteral(formuleNormalisee->getLiteral(-pere));
    c1.addLiteral(formuleNormalisee->getLiteral(filsG));
    c2.addLiteral(formuleNormalisee->getLiteral(-pere));
    c2.addLiteral(formuleNormalisee->getLiteral(filsD));
    c3.addLiteral(formuleNormalisee->getLiteral(pere));
    c3.addLiteral(formuleNormalisee->getLiteral(-filsD));
    c3.addLiteral(formuleNormalisee->getLiteral(-filsG));

    formuleNormalisee->addClause(new Clause(c1));
    formuleNormalisee->addClause(new Clause(c2));
    formuleNormalisee->addClause(new Clause(c3));
}

void TransformationTseitin::addClausesOu(int pere, int filsG, int filsD)
{
    Clause c1(V+nbrVariableAux);
    Clause c2(V+nbrVariableAux);
    Clause c3(V+nbrVariableAux);

    c1.addLiteral(formuleNormalisee->getLiteral(pere));
    c1.addLiteral(formuleNormalisee->getLiteral(-filsG));
    c2.addLiteral(formuleNormalisee->getLiteral(pere));
    c2.addLiteral(formuleNormalisee->getLiteral(-filsD));
    c3.addLiteral(formuleNormalisee->getLiteral(-pere));
    c3.addLiteral(formuleNormalisee->getLiteral(filsD));
    c3.addLiteral(formuleNormalisee->getLiteral(filsG));

    formuleNormalisee->addClause(new Clause(c1));
    formuleNormalisee->addClause(new Clause(c2));
    formuleNormalisee->addClause(new Clause(c3));
}

void TransformationTseitin::addClausesXor(int pere, int filsG, int filsD)
{
    Clause c1(V+nbrVariableAux);
    Clause c2(V+nbrVariableAux);
    Clause c3(V+nbrVariableAux);
    Clause c4(V+nbrVariableAux);

    c1.addLiteral(formuleNormalisee->getLiteral(-pere));
    c1.addLiteral(formuleNormalisee->getLiteral(filsG));
    c1.addLiteral(formuleNormalisee->getLiteral(filsD));

    c2.addLiteral(formuleNormalisee->getLiteral(pere));
    c2.addLiteral(formuleNormalisee->getLiteral(-filsG));
    c2.addLiteral(formuleNormalisee->getLiteral(filsD));

    c3.addLiteral(formuleNormalisee->getLiteral(pere));
    c3.addLiteral(formuleNormalisee->getLiteral(filsD));
    c3.addLiteral(formuleNormalisee->getLiteral(-filsG));

    c4.addLiteral(formuleNormalisee->getLiteral(-pere));
    c4.addLiteral(formuleNormalisee->getLiteral(-filsD));
    c4.addLiteral(formuleNormalisee->getLiteral(-filsG));

    formuleNormalisee->addClause(new Clause(c1));
    formuleNormalisee->addClause(new Clause(c2));
    formuleNormalisee->addClause(new Clause(c3));
    formuleNormalisee->addClause(new Clause(c4));
}

void TransformationTseitin::addClausesImplique(int pere, int filsG, int filsD)
{
    Clause c1(V+nbrVariableAux);
    Clause c2(V+nbrVariableAux);
    Clause c3(V+nbrVariableAux);

    c1.addLiteral(formuleNormalisee->getLiteral(-pere));
    c1.addLiteral(formuleNormalisee->getLiteral(-filsG));
    c1.addLiteral(formuleNormalisee->getLiteral(filsD));

    c2.addLiteral(formuleNormalisee->getLiteral(pere));
    c2.addLiteral(formuleNormalisee->getLiteral(filsG));

    c3.addLiteral(formuleNormalisee->getLiteral(pere));
    c3.addLiteral(formuleNormalisee->getLiteral(-filsD));

    formuleNormalisee->addClause(new Clause(c1));
    formuleNormalisee->addClause(new Clause(c2));
    formuleNormalisee->addClause(new Clause(c3));
}
