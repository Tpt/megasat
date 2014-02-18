#include "../include/Formule.h"
#include<cstdio>
#include<cstdlib>

using namespace std;

Formule::Formule() : V(0), clauses(unordered_set<Clause*>()), vars(vector<Variable*>()), lits_pos(vector<Literal*>()), lits_neg(vector<Literal*>())
{}

Formule::Formule(const int variableNumber) : V(variableNumber), clauses(unordered_set<Clause*>()), vars(vector<Variable*>(variableNumber)), lits_pos(vector<Literal*>(variableNumber)), lits_neg(vector<Literal*>(variableNumber))
{}

Formule::~Formule() ///Pas franchement utile.
{
    for(Clause* c : clauses)
        delete c;
}

int Formule::getVariableNumber() const
{
    return V;
}

void Formule::setLiteral(int id, bool polarite, bool val)
{
    vars[id-1]->setVal( (val && polarite) || (!val && !polarite) ); /// nxor
}

void Formule::setVar(int id, bool val)
{
    vars[id-1]->setVal(val);
}

void Formule::simplifier() ///Arret mortellement dangereux ! Mais garanti 100% safe (a quelques exceptions près).
{
    if(eliminationLiterauxPurs() || propagationUnitaire())
        simplifier();
}

bool Formule::simplificationLiteralPur(int id)
{
    bool found_pos=false;
    bool found_neg=false;
    int res;

    for(Clause* c : clauses)
    {
        res=c->polariteLiteral(lits_pos[id-1],lits_pos[id-1]);
        if(res==1)
            found_pos=true;
        else if(res==-1)
            found_neg=true;
    }

    if(!found_neg && found_pos)
    {
        lits_pos[id-1]->setVal(true);
        compacter();
        return true;
    }
    else if(found_neg && !found_pos)
    {
        lits_neg[id-1]->setVal(true);
        compacter();
        return true;
    }

    return false;
}

void Formule::supprimerTautologies()
{
    for(Clause* c : clauses)
        if(c->isTautologie())
            clauses.erase(c);
}

bool Formule::eliminationLiterauxPurs()
{
    bool modif=false;
    supprimerTautologies();

    for(int id=1; id<V+1; ++id)
        if(simplificationLiteralPur(id))
            modif=true;

    if(modif)
        eliminationLiterauxPurs();

    return modif;
}

void Formule::compacter()
{
    for(Clause* c : clauses)
    {
        c->supprimerLiterauxFaux();
        if(c->contientLiteralVrai())
            clauses.erase(c);

    }
}

bool Formule::propagationUnitaire()
{
    bool modif=false;

    for(Clause* c : clauses)
    {
        if(c->simplificationUnitaire())
            modif=true;
    }

    compacter();

    if(modif)
        propagationUnitaire();

    return modif;
}

vector<Variable*> Formule::getVars() const
{
    return vars;
}

Variable* Formule::getVar(int id) const
{
    return vars[id];
}

Literal* Formule::getLiteral(int id) const
{
    if(id > 0) {
        return lits_pos[id - 1];
    } else {
        return lits_neg[-id - 1];
    }
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

bool Formule::isThereClauseVide() const
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

void Formule::supprimer_surclauses(const Clause* cl)
{
    for(Clause* c : clauses)
        if(c->estSurclause(cl))
            clauses.erase(c);
}

bool Formule::aSousclauses(const Clause* cl) const
{
    for(Clause* c : clauses)
        if(cl->estSurclause(c))
            return true;

    return false;
}

int Formule::eval() const /** Comme à l'accoutumée :
0 => Faux
1 => Vrai
2 => Non encore défini
NB : 0 peut petre renvoyé alors que certaines variables ne sont pas encore définies.
**/
{
    for(Clause* c : clauses)
    {
        int tmp=c->eval();
        if(tmp==2)
            return 2;
        else if(tmp==0)
            return 0;
    }
    return 1;
}

void Formule::init_lits()
{
    for(int i=0; i<V; ++i)
    {
        vars.push_back(new Variable(i+1));
        lits_neg.push_back(new Literal(vars[i],false));
        lits_pos.push_back(new Literal(vars[i],true));
    }
}

Formule::Formule(const Formule& other) : V(other.V), clauses(other.clauses), vars(other.vars), lits_pos(other.lits_pos), lits_neg(other.lits_neg)
{}

Formule::Formule(const int V_e, const vector<Variable*>& vars_e, const vector<Literal*>& lits_pos_e, const vector<Literal*>& lits_neg_e) : V(V_e), clauses(unordered_set<Clause*>()), vars(vars_e), lits_pos(lits_pos_e), lits_neg(lits_neg_e)
{}
