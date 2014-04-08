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

void Formule::simplifier() ///Arret mortellement dangereux ! Mais garanti 100% safe (a quelques exceptions près).
{
    compacter();
    while(eliminationLiterauxPurs() || propagationUnitaire())
        compacter();
}

bool Formule::simplificationLiteralPur(int id)
{
    bool found_pos=false;
    bool found_neg=false;
    Polarite res;

    for(Clause* c : clauses)
    {
        res=c->polariteLiteral(id);
        if(res==POSITIF)
            found_pos=true;
        else if(res==NEGATIF)
            found_neg=true;
    }

    if(!found_neg && found_pos)
    {
        lits_pos[static_cast<size_t>(id-1)]->setVal(true);
        return true;
    }
    else if(found_neg && !found_pos)
    {
        lits_neg[static_cast<size_t>(id-1)]->setVal(true);
        return true;
    }

    return false;
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

bool Formule::eliminationLiterauxPurs()
{
    bool modif=false;

    for(int id=1; id<V+1; ++id)
        if(simplificationLiteralPur(id))
            modif=true;

    return modif;
}

void Formule::compacter()
{
    list<Clause*> clausesASupprimer;
    for(Clause* c : clauses)
    {
        c->supprimerLiterauxFaux();
        if(c->contientLiteralVrai())
            clausesASupprimer.push_front(c); //on ne peut supprimer directement car cela invaliderait l'itérateur
    }

    for(Clause* c : clausesASupprimer)
        clauses.erase(c);
}

bool Formule::propagationUnitaire()
{
    bool modif=false;

    for(Clause* c : clauses)
    {
        if(c->simplificationUnitaire())
            modif=true;
    }

    if(modif)
        propagationUnitaire();

    return modif;
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

int Formule::size() const
{
    return static_cast<int>(clauses.size());
}

bool Formule::isVide() const
{
    return clauses.size() == 0;
}

bool Formule::contientClauseVide() const
{
    for(Clause* c : clauses)
        if(c->isVide())
            return true;
    return false;
}

void Formule::addClause(Clause* clause) ///malgre la structure d'ensemble, le test est indispensable. En effet c'est un pointeur et non l'élément
{
    if(!contient(clause))
        clauses.insert(clause);
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

void Formule::supprimerSurclauses(const Clause* cl)
{
    vector<Clause*> aSupprimer(0);

    for(Clause* c : clauses)
        if(c->estSurclause(cl))
            aSupprimer.push_back(c);

    for(unsigned int m = 0 ; m < aSupprimer.size() ; ++m)
        clauses.erase(aSupprimer[m]);
}

bool Formule::aSousclauses(const Clause* cl) const
{
    for(Clause* c : clauses)
        if(cl->estSurclause(c))
            return true;

    return false;
}

ResultatEvaluation Formule::eval() const
{
    for(Clause* c : clauses)
    {
        int tmp=c->eval();
        if(tmp==2)
            return INCONNU;
        else if(tmp==0)
            return FAUX;
    }
    return VRAI;
}
