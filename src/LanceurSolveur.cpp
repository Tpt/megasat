#include "../include/LanceurSolveur.h"
#include "../include/VariableNonAssigneeProvider.h"
#include "../include/DavisPutnamSolveur.h"
#include "../include/DPLLSolveur.h"
#include "../include/DPLLSurveilleSolveur.h"

using namespace std;

LanceurSolveur::LanceurSolveur(ArgumentsParser& arguments_, string debutCommentaire_, Heuristique heuristiqueParDefaut_) : arguments(arguments_), debutCommentaire(debutCommentaire_), heuristiqueParDefaut(heuristiqueParDefaut_)
{}

LanceurSolveur::~LanceurSolveur()
{}

Formule LanceurSolveur::execute(Formule& formule)
{
    VariableNonAssigneeProvider* heuristique = nullptr;
    switch(getHeuristique())
    {
        case SIMPLE:
            heuristique = new VariableNonAssigneeProviderSimple();
            break;
        case RAND:
            heuristique = new VariableNonAssigneeProviderRand();
            break;
        case MALIN:
            heuristique = new VariableNonAssigneeProviderMalin();
            break;
        case MOMS:
            heuristique = new VariableNonAssigneeProviderMOMS();
            break;
        case DLIS:
            heuristique = new VariableNonAssigneeProviderDLIS();
            break;
    }

    Solveur* solveur = nullptr;
    if(arguments.getOption("dp"))
    {
        solveur = new DavisPutnamSolveur(formule);
    }
    else if(arguments.getOption("wl"))
    {
        solveur = new DPLLSurveilleSolveur(formule, *heuristique);
    }
    else
    {
        solveur = new DPLLSolveur(formule, *heuristique);
    }


    if(solveur->isSatifiable())
    {
        formule = solveur->getFomule();
        delete solveur;
        delete heuristique;
        return formule;
    }
    else
    {
        delete solveur;
        delete heuristique;
        throw InsatisfiableException();
    }
}

Heuristique LanceurSolveur::getHeuristique()
{
    Heuristique heuristique = heuristiqueParDefaut;

    string comment = "Choix des variables non assignées par défaut.";
    
    if(arguments.getOption("rand"))
    {
        heuristique = RAND;
    }
    else if(arguments.getOption("malin"))
    {
        heuristique = MALIN;
    }
    else if(arguments.getOption("moms"))
    {
        heuristique = MOMS;
    }
    else if(arguments.getOption("dlis"))
    {
        heuristique = DLIS;
    }

    if(arguments.getOption("v"))
    {
        ostream out(getBufferSortie());

        switch(heuristique)
        {
            case SIMPLE:
                out << debutCommentaire << " Choix des variables non assignées par défaut." << endl;
                break;
            case RAND:
                out << debutCommentaire << " Choix des variables non assignées de manière aléatoire." << endl;
                break;
            case MALIN:
                out << debutCommentaire << " Choix des variables non assignées suivant leur fréquence d'apparition." << endl;
                break;
            case MOMS:
                out << debutCommentaire << " Choix des variables non assignées avec l'heuristique MOMS." << endl;
                break;
            case DLIS:
                out << debutCommentaire << " Choix des variables non assignées avec l'heuristique DLIS." << endl;
                break;
        }
    }

    return heuristique;
}

streambuf* LanceurSolveur::getBufferSortie()
{
    string outputFileName = arguments.getArgument("outputFile");
    if(outputFileName != "")
    {
        ofstream of;
        of.open(outputFileName);
        return of.rdbuf();
    }
    else
    {
        return cout.rdbuf();
    }
}

vector<string> LanceurSolveur::getNomsOptions()
{
    vector<string> liste(8);
    liste[0]="wl";
    liste[1]="dp";
    liste[2]="rand";
    liste[3]="malin";
    liste[4]="moms";
    liste[5]="dlis";
    liste[6]="v";
    liste[7]="s";
    return liste;
}
