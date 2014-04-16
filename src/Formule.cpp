#include "../include/Formule.h"
#include<cstdio>
#include<cstdlib>
#include<list>

using namespace std;

Formule::Formule(const int variableNumber) : V(variableNumber), clauses(unordered_set<Clause*>()), vars(vector<Variable*>()), lits_pos(vector<Literal*>()), lits_neg(vector<Literal*>())
{
    initLits();
}

Formule::Formule(const Formule& formule) : V(formule.V), clauses(unordered_set<Clause*>()), vars(vector<Variable*>()), lits_pos(vector<Literal*>()), lits_neg(vector<Literal*>())
{
    initLits();

    for(int i = 0; i < V; ++i)
        if(formule.vars[static_cast<size_t>(i)]->isAssignee())
            vars[static_cast<size_t>(i)]->setVal(formule.vars[static_cast<size_t>(i)]->getVal());

    for(Clause* c : formule.clauses)
    {
        unordered_set<Literal*> literaux = c->getLiteraux();
        Clause* w = new Clause(V, c->getUid());
        for(Literal* l : literaux)
        {
            if(l->getPolarite())
                w->addLiteral(lits_pos[static_cast<size_t>(l->getAbsId()-1)]);
            else
                w->addLiteral(lits_neg[static_cast<size_t>(l->getAbsId()-1)]);
        }
        clauses.insert(w);
    }
}

Formule& Formule::operator= (const Formule& other)
{
    Formule temp(other);

    swap(temp.V, this->V);
    swap(temp.clauses, this->clauses);
    swap(temp.vars, this->vars);
    swap(temp.lits_pos, this->lits_pos);
    swap(temp.lits_neg, this->lits_neg);

    return *this;
}

Formule::~Formule()
{
    vector<Clause*> aSupprimer(0);
    for(Clause* c : clauses)
        aSupprimer.push_back(c);
    for(unsigned int i = 0; i < aSupprimer.size(); ++i)
        delete aSupprimer[i];

    for(unsigned int i = 0; i < lits_neg.size(); ++i)
        delete lits_neg[i];
    for(unsigned int i = 0; i < lits_pos.size(); ++i)
        delete lits_pos[i];
    for(unsigned int i = 0; i < vars.size(); ++i)
        delete vars[i];
}

void Formule::initLits()
{
    vars.resize(static_cast<size_t>(V));
    lits_neg.resize(static_cast<size_t>(V));
    lits_pos.resize(static_cast<size_t>(V));

    for(int i = 0; i < V; ++i)
    {
        vars[static_cast<size_t>(i)] = new Variable(i+1);
        lits_neg[static_cast<size_t>(i)] = new Literal(vars[static_cast<size_t>(i)], false);
        lits_pos[static_cast<size_t>(i)] = new Literal(vars[static_cast<size_t>(i)], true);
    }
}

int Formule::getNombreDeVariables() const
{
    return V;
}

void Formule::setLiteral(int id, bool polarite, bool val)
{
    vars[static_cast<size_t>(id-1)]->setVal( (val && polarite) || (!val && !polarite) ); /// nxor
}

void Formule::setVar(int id, bool val)
{
    vars[static_cast<size_t>(id-1)]->setVal(val);
}

void Formule::supprimerTautologies()
{
    vector<Clause*> aSupprimer;
    for(Clause* c : clauses)
        if(c->isTautologie())
            aSupprimer.push_back(c);

    for(unsigned int i=0; i<aSupprimer.size(); ++i)
        clauses.erase(aSupprimer[i]);
}

vector<Variable*> Formule::getVars() const
{
    return vars;
}

vector<Literal*> Formule::getLiterauxPositifs() const
{
    return lits_pos;
}

vector<Literal*> Formule::getLiterauxNegatifs() const
{
    return lits_neg;
}

Variable* Formule::getVar(int id) const
{
    return vars[static_cast<size_t>(id - 1)];
}

Literal* Formule::getLiteral(int id) const
{
    if(id > 0)
        return lits_pos[static_cast<size_t>(id - 1)];
    else
        return lits_neg[static_cast<size_t>(-id - 1)];
}

void Formule::print() const
{
    for(Clause* c : clauses)
        c->print();

    cout<<endl;
}

bool Formule::isVide() const
{
    return clauses.size() == 0;
}

void Formule::addClause(Clause* clause) ///malgre la structure d'ensemble, le test est indispensable. En effet c'est un pointeur et non l'élément
{
    if(!contient(clause))
        clauses.insert(clause);
}

void Formule::addClause(const std::vector<int>& c, int uid)
{
    Clause* w = new Clause(V, uid);
    for(int literalId : c)
    {
        if(literalId > 0)
            w->addLiteral(lits_pos[literalId - 1]);
        else
            w->addLiteral(lits_neg[-literalId - 1]);
    }
    clauses.insert(w);
}

void Formule::addClauses(const unordered_set<Clause*>& clausesAAjouter) ///Le précédent en boucle
{
    for(Clause* clause : clausesAAjouter)
        addClause(clause);
}

void Formule::supprimerClause(Clause* c)
{
    clauses.erase(c);
}

unordered_set<Clause*> Formule::getClauses() const
{
    return clauses;
}

bool Formule::contient(const Clause* clause) const
{
    for(Clause* clause2 : clauses)
        if(*clause == *clause2)
            return true;

    return false;
}
