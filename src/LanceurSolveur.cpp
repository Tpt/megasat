#include "../include/LanceurSolveur.h"
#include "../include/VariableNonAssigneeProvider.h"
#include "../include/DavisPutnamSolveur.h"
#include "../include/DPLLSolveur.h"
#include "../include/DPLLSurveilleSolveur.h"

using namespace std;
using namespace std::chrono;

LanceurSolveur::LanceurSolveur() :
fileName(""), fileSortieName(""), existeFichierSortie(false), verbose(false), avecLiterauxSurveilles(false), utiliserDavisPutnam(false), typeHeuristique(SIMPLE)
{}

LanceurSolveur::~LanceurSolveur()
{}

void LanceurSolveur::parseOptions(int argc, char* argv[])
{
    bool entreeTrouve = false;
    for(int i = 1; i < argc; i++)
    {
        if( argv[i][0] == '-' )
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
                cerr << "c Option inconnue : " << argv[i] << endl;
        }
        else
        {
            if(!entreeTrouve)
            {
                fileName = argv[i];
                entreeTrouve = true;
            }
            else
            {
                fileSortieName = argv[i];
                existeFichierSortie = true;
            }
        }
    }

    if(fileName == "")
    {
        cerr << "c Pas de fichier donné en entrée.\nc Fin de la résolution." << endl;
        exit(EXIT_FAILURE);
    }
}

Formule LanceurSolveur::execute(Formule& formule)
{
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

string LanceurSolveur::getFileName() const
{
    return fileName;
}

bool LanceurSolveur::isVerbose() const
{
    return verbose;
}

streambuf* LanceurSolveur::getBufferSortie() const
{
    if(existeFichierSortie)
    {
        ofstream of;
        of.open(fileSortieName);
        return of.rdbuf();
    }
    else
    {
        return cout.rdbuf();
    }
}
