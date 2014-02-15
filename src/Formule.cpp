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

void Formule::addClause(Clause* clause) ///malgré la structure d'ensemble, le test est indispensable. En effet c est un pointeur et non l'élément
{
    if(!contient(clause))
        clauses.insert(clause);
}

void Formule::addClauses(const unordered_set<Clause*>& clauses) ///Le précédent en boucle
{
    for(Clause* clause : clauses)
        addClause(clause);
}

Clause* Formule::resolution(const Clause* c1, Clause* c2, const int id) const
{
    Clause* sortie = new Clause(*c1);
    sortie->fusionner(c2);
    sortie->supprimer(lits_pos[id-1]);
    sortie->supprimer(lits_neg[id-1]);
    return sortie;
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

Formule* Formule::resoudre_seau(const Formule* seau, int id) const
{
    unordered_set<Clause*> pos;
    unordered_set<Clause*> neg;
    unordered_set<Clause*> autres;
    unordered_set<Clause*> all(seau->getClauses());
    Formule* sortie=new Formule(V,size(),vars,lits_pos,lits_neg);
    Clause* work;

    for(Clause* c : all) ///S√©pare les polarit√©s
    {
        if(c->polariteLiteral(lits_pos[id-1],lits_neg[id-1])==1)
            pos.insert(c);
        else if(c->polariteLiteral(lits_pos[id-1],lits_neg[id-1])==-1)
            neg.insert(c);
        else
            autres.insert(c);
    }
    sortie->addClauses(autres);

    unsigned int i=0;
    unsigned int j=0;
    for(unordered_set<Clause*>::iterator it=pos.begin(); it!=pos.end(); ++it,++i) ///On double-boucle pour faire toutes les r√©solutions...
    {
        printf("c ["); /// Affichage !
        unsigned int l=0;
        for(; l<i*50/pos.size(); ++l)
            printf("#");
        for(; l<50; ++l)
            printf(" ");
        printf("] %d%%",i*100/static_cast<int>(pos.size()));
        j=0;
        for(unordered_set<Clause*>::iterator jt=neg.begin(); jt!=neg.end(); ++jt,++j)
        {
            work=resolution(*it, *jt, id);
            if(work->isVide()) ///Si on a une clause si, c'est fini et on interromp avec une exception.
            {
                for(l=0; l<58; ++l) ///Gestion du cas particulier
                    printf("\b");
                if(i*100/pos.size()==100)
                    printf("\b");
                printf("\n");
                throw 1;
            }
            if(!work->isTautologie()&& !sortie->aSousclauses(work) && !sortie->contient(work) ) /** C'est l√† que c'est un peu fin.
            On ne prend pas les tautologies, les surclauses de clauses d√©ja existentes et les doublons.
            **/
            {
                sortie->supprimer_surclauses(work); /// On enl√®ve toutes les surclauses qui sont n√©cessairement v√©rifi√©es.
                sortie->addClause(work);
            }
        }
        for(l=0; l<58; ++l) ///Suite de l'affichage
            printf("\b");
        if(i*100/pos.size()==100)
            printf("\b");
    }
    printf("c ["); ///Et fin de la magnifique interface utilisateur !
    int l=0;
    for(; l<50; ++l)
        printf("#");
    printf("] 100%%\n");

    return sortie;
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

void Formule::fusionner(const Formule* e, vector<Formule*> seaux) const ///Ajoute les clauses d'une formule dans les bons seaux
{
    unordered_set<Clause*> t=e->getClauses();

    for(Clause* c:t)
        seaux[c->indiceMax()-1]->addClause(c);
}

void Formule::chercher_assignation(Formule* f, int id) ///On essaie avec l'un et si ça ne marche pas, on prend l'autre...
{
    vars[id]->setVal(true);
    if(f->eval()!=1)
        vars[id]->setVal(false);
}

void Formule::solve()
{
    vector<Formule*> seaux(0);

    for(int i=0; i<V; ++i) /// On cr√©e les seaux.
        seaux.push_back(new Formule(0,0,vars,lits_pos,lits_neg));

    for(Clause* c : clauses) /// On remplit les seaux.
        if(!c->isTautologie())
            seaux[c->indiceMax()-1]->addClause(c);

    try ///Observez bien l'astucieux try/catch !
    {
        cout<<"c "<<"Nombre de seaux : "<<V<<endl;
        for(int i=V; i>0; --i) ///Les r√©solutions dans le sens descendant
        {
            cout<<"c "<<"Seau "<<i<<" :"<<endl;
            fusionner(resoudre_seau(seaux[i-1],i),seaux);
        }

        for(int i=0; i<V; ++i) ///La remont√©
            chercher_assignation(seaux[i], i);

        cout<<"s SATISFIABLE"<<endl; ///Affiche la solution si aucune exception n'est lanc√©e ie si la formule est satisfiable
        for(int i=0; i<V; ++i)
        {
            if(vars[i]->getVal())
                cout<<"v "<<i+1<<endl;
            else
                cout<<"v "<<-i-1<<endl;
        }
    }
    catch(int e)
    {
        cout<<"s UNSATISFIABLE"<<endl;
    }
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

Formule::Formule(const int V_e, const int C_e, const vector<Variable*>& vars_e, const vector<Literal*>& lits_pos_e, const vector<Literal*>& lits_neg_e) : V(V_e), clauses(unordered_set<Clause*>()), vars(vars_e), lits_pos(lits_pos_e), lits_neg(lits_neg_e)
{}
