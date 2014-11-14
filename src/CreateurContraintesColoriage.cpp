#include "../include/CreateurContraintesColoriage.h"
#include<cmath>
#include<sstream>

using namespace std;

CreateurContraintesColoriage::CreateurContraintesColoriage(Graphe &graphe_, int k_)
: graphe(graphe_), k(k_), tailleCodeCouleurSommet(1)
{
    if(k_ > 1)
        tailleCodeCouleurSommet = static_cast<int>(ceil(log2(k_)));
}

FormuleTseitin<pair<int,int>>* CreateurContraintesColoriage::cree() const
{
    //initialisation toujours vrai (simplifie concidérablement l'écriture du code)
    FormuleTseitin<pair<int,int>>* formule = new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::OU, creeVariable(0, 0), new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::NON, creeVariable(0, 0)));

    for(int i = 0; i < graphe.getSommetNumber(); i++)
    {
        FormuleTseitin<pair<int,int>>* contrainte = creeContrainteInferieurK(i);
        if(contrainte != nullptr)
            formule = new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::ET, contrainte, formule);
    }

    for(Arete arete : graphe.getAretes())
        formule = new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::ET, creeContrainteArete(arete), formule);

    return formule;
}

FormuleTseitin<pair<int,int>>* CreateurContraintesColoriage::creeContrainteInferieurK(int sommet) const
{
    FormuleTseitin<pair<int,int>>* formule = nullptr;
    int reste = k;

    for(int i = 0; i < tailleCodeCouleurSommet; i++)
    {
        if(formule == nullptr)
        {
            if(reste % 2 == 1)
            {
                formule = new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::NON, creeVariable(sommet, i));
            }
        }
        else
        {
            if(reste % 2 == 1)
                formule = new FormuleTseitin<pair<int,int>>(
                    FormuleTseitin<pair<int,int>>::OU,
                    new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::NON, creeVariable(sommet, i)),
                    formule
                );
            else
                formule = new FormuleTseitin<pair<int,int>>(
                        FormuleTseitin<pair<int,int>>::ET,
                        new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::NON, creeVariable(sommet, i)),
                        formule
                );
        }

        reste /= 2;
    }

    return formule;
}

FormuleTseitin<pair<int,int>>* CreateurContraintesColoriage::creeContrainteArete(Arete arete) const
{
    int extremiteGauche = arete.getExtremiteGauche();
    int extremiteDroite = arete.getExtremiteDroite();

    FormuleTseitin<pair<int,int>>* formule = new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::XOR, creeVariable(extremiteGauche, 0), creeVariable(extremiteDroite, 0));

    for(int i = 1; i < tailleCodeCouleurSommet; i++)
        formule = new FormuleTseitin<pair<int,int>>(
            FormuleTseitin<pair<int,int>>::OU,
            formule,
            new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::XOR, creeVariable(extremiteGauche, i), creeVariable(extremiteDroite, i))
        );

    return formule;
}

inline FormuleTseitin<pair<int,int>>* CreateurContraintesColoriage::creeVariable(int sommet, int bit) const
{
    return new FormuleTseitin<pair<int,int>>(FormuleTseitin<pair<int,int>>::VARIABLE, pair<int,int>(sommet, bit));
}
