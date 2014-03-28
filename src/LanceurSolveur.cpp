#include "../include/LanceurSolveur.h"
#include "../include/VariableNonAssigneeProvider.h"
#include "../include/DavisPutnamSolveur.h"
#include "../include/DPLLSolveur.h"
#include "../include/DPLLSurveilleSolveur.h"

using namespace std;
using namespace std::chrono;

LanceurSolveur::LanceurSolveur(ArgumentsParser& arguments_) : arguments(arguments_)
{}

LanceurSolveur::~LanceurSolveur()
{}

Formule LanceurSolveur::execute(Formule& formule)
{
    VariableNonAssigneeProvider* heuristique = new VariableNonAssigneeProviderSimple();
    if(arguments.getOption("rand"))
    {
        cout << "c Choix des variables non assignées de manière aléatoire." << endl;
        heuristique = new VariableNonAssigneeProviderRand();
    }
    else if(arguments.getOption("malin"))
    {
        cout << "c Choix des variables non assignées suivant leur fréquence d'apparition." << endl;
        heuristique = new VariableNonAssigneeProviderMalin();
    }
    else if(arguments.getOption("moms"))
    {
        cout << "c Choix des variables non assignées avec l'heuristique MOMS." << endl;
        heuristique = new VariableNonAssigneeProviderMOMS();
    }
    else if(arguments.getOption("dlis"))
    {
        cout << "c Choix des variables non assignées avec l'heuristique DLIS." << endl;
        heuristique = new VariableNonAssigneeProviderDLIS();
    }
    else
    {
        cout << "c Choix des variables non assignées par défaut." << endl;
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
        return formule;
    }
    else
    {
        delete solveur;
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

vector<string> LanceurSolveur::getNomsOptions() {
    return {"wl", "dp", "rand", "malin", "moms", "dlis", "v", "s"};
}