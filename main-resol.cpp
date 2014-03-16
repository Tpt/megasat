#include<cstdlib>
#include<cstring>
#include<chrono>
#include"include/Formule.h"
#include"include/CnfParser.h"
#include"include/DavisPutnamSolveur.h"
#include"include/DPLLSolveur.h"
#include"include/DPLLSurveilleSolveur.h"

using namespace std;
using namespace std::chrono;

enum Heuristique {
    SIMPLE,
    RAND,
    MALIN,
    MOMS,
    DLIS
};

Formule parseCnfFile(string fileName)
{
    CnfParser cnfParser;

    try
    {
        return cnfParser.parse(fileName);
    }
    catch(ParseError& e)
    {
        cerr << "c Erreur du parser : " << e.getMessage() << "\nc Arrêt de la résolution." << endl;
        exit( EXIT_FAILURE );
    }
}

int main(int argc, char *argv[])
{
    string fileName = "";
    bool avecLiterauxSurveilles = false;
    bool utiliserDavisPutnam = false;
    Heuristique typeHeuristique = SIMPLE;

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
        else
            fileName = argv[i];
    }

    if(fileName == "")
    {
        cerr << "c Pas de fichier donné en entrée.\nc Fin de la résolution." << endl;
        return EXIT_FAILURE;
    }

    Formule formule = parseCnfFile(fileName);

    auto beginTime = system_clock::now();

    VariableNonAssigneeProvider* heuristique;
    switch(typeHeuristique)
    {
        case SIMPLE:
            cout << "c Choix des variables non assignées par défaut." << endl;
            heuristique = new VariableNonAssigneeProviderSimple();
            break;
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

    return EXIT_SUCCESS;
}
