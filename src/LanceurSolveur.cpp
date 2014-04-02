#include "../include/LanceurSolveur.h"
#include "../include/VariableNonAssigneeProvider.h"
#include "../include/DavisPutnamSolveur.h"
#include "../include/DPLLSolveur.h"
#include "../include/DPLLSurveilleSolveur.h"

using namespace std;

LanceurSolveur::LanceurSolveur(ArgumentsParser& arguments_, string debutCommentaire_, SolveurType solveurParDefaut_, HeuristiqueType heuristiqueParDefaut_) : arguments(arguments_), debutCommentaire(debutCommentaire_), solveurParDefaut(solveurParDefaut_), heuristiqueParDefaut(heuristiqueParDefaut_)
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
    switch(getSolveur())
    {
        case DPLL:
            solveur = new DPLLSolveur(formule, *heuristique);
            break;
        case WATCHED_LITERALS:
            solveur = new DPLLSurveilleSolveur(formule, *heuristique);
            break;
        case DAVIS_PUTNAM:
            solveur = new DavisPutnamSolveur(formule);
            break;
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

SolveurType LanceurSolveur::getSolveur()
{
    SolveurType solveur = solveurParDefaut;

    if(arguments.getOption("dpll"))
    {
        solveur = DPLL;
    }
    else if(arguments.getOption("wl"))
    {
        solveur = WATCHED_LITERALS;
    }
    else if(arguments.getOption("dp"))
    {
        solveur = DAVIS_PUTNAM;
    }
    
    if(arguments.getOption("v"))
    {
        ostream out(getBufferSortie());
        
        switch(solveur)
        {
            case DPLL:
                out << debutCommentaire << " Utilisation de PDLL." << endl;
                break;
            case WATCHED_LITERALS:
                out << debutCommentaire << " Utilisation des Watched Literals." << endl;
                break;
            case DAVIS_PUTNAM:
                out << debutCommentaire << " Utilisation de Davis Putnam." << endl;
                break;
        }
    }

    return solveur;
}

HeuristiqueType LanceurSolveur::getHeuristique()
{
    HeuristiqueType heuristique = heuristiqueParDefaut;
    
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
    vector<string> liste(9);
    liste[0]="dpll";
    liste[1]="wl";
    liste[2]="dp";
    liste[3]="rand";
    liste[4]="malin";
    liste[5]="moms";
    liste[6]="dlis";
    liste[7]="v";
    liste[8]="s";
    return liste;
}
