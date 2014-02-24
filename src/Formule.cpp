#include "../include/Formule.h"
#include<cstdio>
#include<cstdlib>
#include<list>

using namespace std;

Formule::Formule(const Formule& formule) : V(formule.V), clauses(unordered_set<Clause*>()), vars(vector<Variable*>()), lits_pos(vector<Literal*>()), lits_neg(vector<Literal*>())
{
    Clause* w;
    unordered_set<Literal*> in;
    unordered_set<Literal*> out;
    init_lits();

    for(int i=0;i<V;++i)
        if(formule.vars[i]->isAssignee())
            vars[i]->setVal(formule.vars[i]->getVal());

    for(Clause* c : formule.clauses)
    {
        in=c->getLiteraux();
        out.clear();
        w=new Clause(V,c->getUid());
        for(Literal* l : in)
        {
            if(l->getPolarite())
                out.insert(lits_pos[l->getAbsId()-1]);
            else
                out.insert(lits_neg[l->getAbsId()-1]);
        }
        w->addLiteraux(out);
        clauses.insert(w);
    }
}

Formule::Formule(const int variableNumber) : V(variableNumber), clauses(unordered_set<Clause*>()), vars(vector<Variable*>()), lits_pos(vector<Literal*>()), lits_neg(vector<Literal*>())
{
    init_lits();
}

Formule::~Formule() ///Pas franchement utile.
{
}

int Formule::getNombreDeVariables() const
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
        lits_pos[id-1]->setVal(true);
        return true;
    }
    else if(found_neg && !found_pos)
    {
        lits_neg[id-1]->setVal(true);
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
        clauses.erase( c );
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
    return vars[id];
}

Literal* Formule::getLiteral(int id) const
{
    if(id > 0)
        return lits_pos[id - 1];
    else
        return lits_neg[-id - 1];
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

void Formule::init_lits()
{
    vars.resize(V);
    lits_neg.resize(V);
    lits_pos.resize(V);

    for(int i=0; i<V; ++i)
    {
        vars[i] = new Variable(i+1);
        lits_neg[i] = new Literal(vars[i],false);
        lits_pos[i] = new Literal(vars[i],true);
    }
}

Formule::Formule(const int V_e, const vector<Variable*>& vars_e, const vector<Literal*>& lits_pos_e, const vector<Literal*>& lits_neg_e) : V(V_e), clauses(unordered_set<Clause*>()), vars(vars_e), lits_pos(lits_pos_e), lits_neg(lits_neg_e)
{}
