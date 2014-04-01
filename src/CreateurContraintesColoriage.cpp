#include "../include/CreateurContraintesColoriage.h"
#include<cmath>
#include<sstream>

using namespace std;

CreateurContraintesColoriage::CreateurContraintesColoriage(Graphe &graphe_, int k_)
: graphe(graphe_), k(k_)
{
    if(k_ <= 1)
        tailleCodeCouleurSommet = 1;
    else
        tailleCodeCouleurSommet = static_cast<int>(ceil(log2(k_)));
}

FormuleTseitin* CreateurContraintesColoriage::cree() const
{
    //initialisation toujours vrai (simplifie concidérablement l'écriture du code)
    FormuleTseitin* formule = new FormuleTseitin(FormuleTseitin::OU, creeVariable(0, 0), new FormuleTseitin(FormuleTseitin::NON, creeVariable(0, 0)));

    for(int i = 0; i < graphe.getSommetNumber(); i++)
    {
        FormuleTseitin* contrainte = creeContrainteInferieurK(i);
        if(contrainte != nullptr)
            formule = new FormuleTseitin(FormuleTseitin::ET, contrainte, formule);
    }

    for(Arete arete : graphe.getAretes())
        formule = new FormuleTseitin(FormuleTseitin::ET, creeContrainteArete(arete), formule);

    return formule;
}

FormuleTseitin* CreateurContraintesColoriage::creeContrainteInferieurK(int sommet) const
{
    FormuleTseitin* formule = nullptr;
    int reste = k;

    for(int i = 0; i < tailleCodeCouleurSommet; i++)
    {
        if(formule == nullptr)
        {
            if(reste % 2 == 1)
            {
                formule = new FormuleTseitin(FormuleTseitin::NON, creeVariable(sommet, i));
            }
        }
        else
        {
            if(reste % 2 == 1)
                formule = new FormuleTseitin(
                    FormuleTseitin::OU,
                    new FormuleTseitin(FormuleTseitin::NON, creeVariable(sommet, i)),
                    formule
                );
            else
                formule = new FormuleTseitin(
                        FormuleTseitin::ET,
                        new FormuleTseitin(FormuleTseitin::NON, creeVariable(sommet, i)),
                        formule
                );
        }

        reste /= 2;
    }

    return formule;
}

FormuleTseitin* CreateurContraintesColoriage::creeContrainteArete(Arete arete) const
{
    int extremiteGauche = arete.getExtremiteGauche();
    int extremiteDroite = arete.getExtremiteDroite();

    FormuleTseitin* formule = new FormuleTseitin(FormuleTseitin::XOR, creeVariable(extremiteGauche, 0), creeVariable(extremiteDroite, 0));

    for(int i = 1; i < tailleCodeCouleurSommet; i++)
        formule = new FormuleTseitin(
            FormuleTseitin::OU,
            formule,
            new FormuleTseitin(FormuleTseitin::XOR, creeVariable(extremiteGauche, i), creeVariable(extremiteDroite, i))
        );

    return formule;
}

FormuleTseitin* CreateurContraintesColoriage::creeVariable(int sommet, int bit) const
{
    ostringstream os;
    os << sommet << '-' << bit;
    return new FormuleTseitin(FormuleTseitin::VARIABLE, os.str());
}
