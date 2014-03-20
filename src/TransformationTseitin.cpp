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

int TransformationTseitin::compterVariablesAux() ///Renvoie le nombre de variables auxilliaires à créer.
{
    int count=1;
    stack<FormuleTseitinSimple> pile;
    FormuleTseitinSimple w;

    pile.push(*formule);

    while(!pile.empty())
    {
        w=pile.top();
        pile.pop();
        if(w.getType()==FormuleTseitinSimple::VARIABLE)
        {
            continue;
        }
        else if(w.getArite()==1)
        {
            count++;
            pile.push(w.getOperande());
        }
        else if(w.getArite()==2)
        {
            count+=2;
            pile.push(w.getOperandeD());
            pile.push(w.getOperandeG());
        }

    }

    return count;
}

void TransformationTseitin::addClausesVariable(int varCourrante, string name)
{
    Clause c1(V+nbrVariableAux);
    Clause c2(V+nbrVariableAux);

    c1.addLiteral(formuleNormalisee->getLiteral(-varCourrante));
    c1.addLiteral(formuleNormalisee->getLiteral(correspondanceDesVariables[name]));
    c2.addLiteral(formuleNormalisee->getLiteral(varCourrante));
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

void TransformationTseitin::parcours()
{
    stack<pair<FormuleTseitinSimple,int> > pile;
    int varCourrante=V+1;
    FormuleTseitinSimple w;
    int v;
    vector<FormuleTseitinSimple*> aSupprimer;

    pile.push(pair<FormuleTseitinSimple,int> (*formule, varCourrante));

    while(!pile.empty())
    {
        v=pile.top().second;
        w=pile.top().first;

        pile.pop();
        if(w.getType()==FormuleTseitinSimple::VARIABLE)
        {
            addClausesVariable(v, w.getName());
        }
        else if(w.getType()==FormuleTseitinSimple::NON)
        {
            ++varCourrante;
            addClausesNon(v,varCourrante);
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperande(),varCourrante));
        }
        else if(w.getType()==FormuleTseitinSimple::ET)
        {
            ++varCourrante;
            addClausesEt(v,varCourrante, varCourrante+1);
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperandeD(),varCourrante+1));
            ++varCourrante;
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperandeG(),varCourrante-1));
        }
        else if(w.getType()==FormuleTseitinSimple::OU)
        {
            ++varCourrante;
            addClausesOu(v,varCourrante, varCourrante+1);
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperandeD(),varCourrante+1));
            ++varCourrante;
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperandeG(),varCourrante-1));
        }
        else if(w.getType()==FormuleTseitinSimple::IMPLIQUE)
        {
            ++varCourrante;
            addClausesImplique(v,varCourrante, varCourrante+1);
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperandeD(),varCourrante+1));
            ++varCourrante;
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperandeG(),varCourrante-1));
        }
        else if(w.getType()==FormuleTseitinSimple::XOR)
        {
            ++varCourrante;
            addClausesXor(v,varCourrante, varCourrante+1);
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperandeG(),varCourrante+1));
            ++varCourrante;
            pile.push(pair<FormuleTseitinSimple,int>(w.getOperandeD(),varCourrante-1));
        }
    }

    for(FormuleTseitinSimple* e : aSupprimer)
        delete e;
}

Formule TransformationTseitin::normaliser()
{
    parcours();
    return *formuleNormalisee;
}
