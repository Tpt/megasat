#include<vector>
#include<unordered_set>
#include "../include/DavisPutnamSolveur.h"
#include "../include/InsatisfiableException.h"

using namespace std;

DavisPutnamSolveur::DavisPutnamSolveur(Formule &formule_) : Solveur(formule_)
{}

DavisPutnamSolveur::~DavisPutnamSolveur()
{}

bool DavisPutnamSolveur::isSatifiable()
{
    formule.supprimerTautologies();

    vector<unordered_set<Clause*> > seaux(0);

    unordered_set<Clause*> clauses(formule.getClauses());
    int V=formule.getNombreDeVariables();
    vector<Variable*> vars (formule.getVars());
    vector<Literal*> lits_neg (formule.getLiterauxNegatifs());
    vector<Literal*> lits_pos (formule.getLiterauxPositifs());

    for(int i = 0; i < V; ++i) /// On crée les seaux.
        seaux.push_back(unordered_set<Clause*>());



    for(Clause* c : clauses) /// On remplit les seaux.
        if(!c->isTautologie())
            seaux[static_cast<size_t>(c->indiceMax()-1)].insert(c);

    try
    {
        for(int i = V; i > 0; i--) ///Les résolutions dans le sens descendant
            fusionner(resoudreSeau(seaux[static_cast<size_t>(i-1)],i),seaux);

        for(int i = 0; i < V; i++) ///La remonté
            chercherAssignation(seaux[static_cast<size_t>(i)], i);

        return true;
    }
    catch(InsatisfiableException)
    {
        return false;
    }
}

unordered_set<Clause*> DavisPutnamSolveur::resoudreSeau(const unordered_set<Clause*>& seau, int id) const
{
    unordered_set<Clause*> pos;
    unordered_set<Clause*> neg;
    unordered_set<Clause*> autres;

    vector<Variable*> vars (formule.getVars());
    vector<Literal*> lits_neg (formule.getLiterauxNegatifs());
    vector<Literal*> lits_pos (formule.getLiterauxPositifs());

    unordered_set<Clause*> sortie;
    Clause* work;

    for(Clause* c : seau) ///Sépare les polarités
    {
        if(c->polariteLiteral(id)==POSITIF)
            pos.insert(c);
        else if(c->polariteLiteral(id)==NEGATIF)
            neg.insert(c);
        else
            autres.insert(c);
    }
    for(Clause* c : autres)
        sortie.insert(c);

    unsigned int i=0;
    for(unordered_set<Clause*>::iterator it=pos.begin(); it!=pos.end(); ++it,++i) ///On double-boucle pour faire toutes les résolutions...
    {
        printf("c ["); /// Affichage !
        unsigned int l=0;
        for(; l<i*50/pos.size(); ++l)
            printf("#");
        for(; l<50; ++l)
            printf(" ");
        printf("] %d%%",static_cast<int>(i*100)/static_cast<int>(pos.size()));
        unsigned int j=0;
        for(unordered_set<Clause*>::iterator jt=neg.begin(); jt!=neg.end(); ++jt,++j)
        {
            work=resolution(*it, *jt, id);
            if(work->isVide()) ///Si on a une clause si, c'est fini et on interrompt avec une exception.
            {
                for(l=0; l<58; ++l) ///Gestion du cas particulier
                    printf("\b");
                if(i*100/pos.size()==100)
                    printf("\b");
                printf("\n");
                delete work;
                throw InsatisfiableException();
            }
            if(!work->isTautologie() && !aSousclauses(sortie, work) && !contient(sortie, work) ) /** C'est là  que c'est un peu fin.
                                                                                                 On ne prend pas les tautologies, les surclauses de clauses déja existentes et les doublons.
                                                                                                **/
            {
                vector<Clause*> aSupprimer(0);/// On enlève toutes les surclauses qui sont nécessairement vérifiées.

                for(Clause* c : sortie)
                    if(c->isSurclause(work))
                        aSupprimer.push_back(c);

                for(unsigned int m = 0 ; m < aSupprimer.size() ; ++m)
                    sortie.erase(aSupprimer[m]);

                sortie.insert(work);
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

void DavisPutnamSolveur::fusionner(const unordered_set<Clause*>& e, vector<unordered_set<Clause*> >& seaux) const ///Ajoute les clauses d'une formule dans les bons seaux
{
    for(Clause* c : e)
        seaux[static_cast<size_t>(c->indiceMax()-1)].insert(c);
}

void DavisPutnamSolveur::chercherAssignation(unordered_set<Clause*>& f, int id) ///On essaie avec l'un et si ça ne marche pas, on prend l'autre...
{
    formule.setVar(id + 1, true);
    if(eval(f) != VRAI)
        formule.setVar(id + 1, false);
}


Clause* DavisPutnamSolveur::resolution(const Clause* c1, Clause* c2, const int id) const
{
    Clause* sortie = new Clause(*c1);
    sortie->fusionner(c2);
    sortie->supprimer(formule.getLiteral(id));
    sortie->supprimer(formule.getLiteral(-id));
    return sortie;
}

bool DavisPutnamSolveur::aSousclauses(const unordered_set<Clause*>& seau, const Clause* cl) const
{
    for(Clause* c : seau)
        if(cl->isSurclause(c))
            return true;

    return false;
}

bool DavisPutnamSolveur::contient(const unordered_set<Clause*>& seau, const Clause* clause) const
{
    for(Clause* clause2 : seau)
        if(*clause == *clause2)
            return true;

    return false;
}

ResultatEvaluation DavisPutnamSolveur::eval(const unordered_set<Clause*>& seau) const
{
    for(Clause* c : seau)
    {
        int tmp=c->eval();
        if(tmp==2)
            return INCONNU;
        else if(tmp==0)
            return FAUX;
    }
    return VRAI;
}

