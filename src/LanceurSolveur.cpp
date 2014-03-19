#include "../include/LanceurSolveur.h"
#include "../include/VariableNonAssigneeProvider.h"
#include "../include/DavisPutnamSolveur.h"
#include "../include/DPLLSolveur.h"
#include "../include/DPLLSurveilleSolveur.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

LanceurSolveur::LanceurSolveur() :
fileName(""), verbose(false), avecLiterauxSurveilles(false), utiliserDavisPutnam(false), typeHeuristique(SIMPLE)
{}

LanceurSolveur::~LanceurSolveur()
{}

void LanceurSolveur::parseOptions(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-wl") == 0)
            avecLiterauxSurveilles = true;
        else if(strcmp(argv[i], "-dp") == 0)
            utiliserDavisPutnam = true;
        else if(strcmp(argv[i], "-rand") == 0)
            typeHeuristique = RAND;
        else if(strcmp(argv[i], "-malin") == 0)
            typeHeuristique = MALIN;
        else if(strcmp(argv[i], "-moms") == 0)
            typeHeuristique = MOMS;
        else if(strcmp(argv[i], "-dlis") == 0)
            typeHeuristique = DLIS;
        else if(strcmp(argv[i], "-v") == 0)
            verbose = true;
        else
            fileName = argv[i];
    }

    if(fileName == "")
    {
        cerr << "c Pas de fichier donné en entrée.\nc Fin de la résolution." << endl;
        exit(EXIT_FAILURE);
    }
}

void LanceurSolveur::ExecuteEtAfficheResultat(Formule& formule)
{
    auto beginTime = system_clock::now();

    VariableNonAssigneeProvider* heuristique = new VariableNonAssigneeProviderSimple();
    switch(typeHeuristique)
    {
        case RAND:
            cout << "c Choix des variables non assignées de manière aléatoire." << endl;
            heuristique = new VariableNonAssigneeProviderRand();
            break;
        case MALIN:
            cout << "c Choix des variables non assignées suivant leur fréquence d'apparition." << endl;
            heuristique = new VariableNonAssigneeProviderMalin();
            break;
        case MOMS:
            cout << "c Choix des variables non assignées avec l'heuristique MOMS." << endl;
            heuristique = new VariableNonAssigneeProviderMOMS();
            break;
        case DLIS:
            cout << "c Choix des variables non assignées avec l'heuristique DLIS." << endl;
            heuristique = new VariableNonAssigneeProviderDLIS();
            break;
        case SIMPLE:
        default:
            cout << "c Choix des variables non assignées par défaut." << endl;
            break;
    }

    Solveur* solveur = nullptr;
    if(utiliserDavisPutnam)
    {
        solveur = new DavisPutnamSolveur(formule);
    }
    else if(avecLiterauxSurveilles)
    {
        solveur = new DPLLSurveilleSolveur(formule, *heuristique);
    }
    else
    {
        solveur = new DPLLSolveur(formule, *heuristique);
    }

    if(solveur->isSatifiable())
    {
        Formule formuleResolue = solveur->getFomule();
        cout << "s SATISFIABLE" << endl;
        for(int i = 1; i <= formuleResolue.getNombreDeVariables(); i++)
        {
            if(formuleResolue.getVar(i)->getVal())
                cout << "v " << i << endl;
            else
                cout << "v " << -i << endl;
        }
    }
    else
    {
        cout << "s UNSATISFIABLE" << endl;
    }
    delete solveur;

    cout << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;

}

string LanceurSolveur::getFileName() const
{
    return fileName;
}

bool LanceurSolveur::isVerbose() const
{
    return verbose;
}
