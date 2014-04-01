#include "../include/LanceurSolveur.h"
#include "../include/VariableNonAssigneeProvider.h"
#include "../include/DavisPutnamSolveur.h"
#include "../include/DPLLSolveur.h"
#include "../include/DPLLSurveilleSolveur.h"

using namespace std;

LanceurSolveur::LanceurSolveur(ArgumentsParser& arguments_, string debutCommentaire_) : arguments(arguments_), debutCommentaire(debutCommentaire_)
{}

LanceurSolveur::~LanceurSolveur()
{}

Formule LanceurSolveur::execute(Formule& formule)
{
    VariableNonAssigneeProvider* heuristique = new VariableNonAssigneeProviderSimple();
    string comment = "Choix des variables non assignées par défaut.";

    if(arguments.getOption("rand"))
    {
        comment = "Choix des variables non assignées de manière aléatoire.";
        heuristique = new VariableNonAssigneeProviderRand();
    }
    else if(arguments.getOption("malin"))
    {
        comment = "Choix des variables non assignées suivant leur fréquence d'apparition.";
        heuristique = new VariableNonAssigneeProviderMalin();
    }
    else if(arguments.getOption("moms"))
    {
        comment = "Choix des variables non assignées avec l'heuristique MOMS.";
        heuristique = new VariableNonAssigneeProviderMOMS();
    }
    else if(arguments.getOption("dlis"))
    {
        comment = "Choix des variables non assignées avec l'heuristique DLIS.";
        heuristique = new VariableNonAssigneeProviderDLIS();
    }
    ostream out(getBufferSortie());
    out << debutCommentaire << ' ' << comment << endl;

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
