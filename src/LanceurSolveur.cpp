#include "../include/LanceurSolveur.h"
#include "../include/VariableNonAssigneeProvider.h"
#include "../include/DavisPutnamSolveur.h"
#include "../include/DPLLSolveur.h"
#include "../include/DPLLSurveilleSolveur.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

LanceurSolveur::LanceurSolveur() :
fileName(""), fileSortieName(""), existeFichierSortie(false), verbose(false), avecLiterauxSurveilles(false), utiliserDavisPutnam(false), typeHeuristique(SIMPLE), utiliseCorrespondance(false), correspondance(std::map<std::string,int>())
{}

LanceurSolveur::~LanceurSolveur()
{}

void LanceurSolveur::utiliserCorrespondance(map<string,int> corr)
{
    correspondance=corr;
    utiliseCorrespondance=true;
}

void LanceurSolveur::parseOptions(int argc, char* argv[])
{
    bool entreeTrouve=false;
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

void LanceurSolveur::executeEtAfficheResultat(Formule& formule)
{
    streambuf * buf;
    ofstream of;

    if(existeFichierSortie)
    {
        of.open(fileSortieName);
        buf = of.rdbuf();
    }
    else
    {
        buf = cout.rdbuf();
    }

    ostream out(buf);

    auto beginTime = system_clock::now();

    VariableNonAssigneeProvider* heuristique = new VariableNonAssigneeProviderSimple();
    switch(typeHeuristique)
    {
        case RAND:
            out << "c Choix des variables non assignées de manière aléatoire." << endl;
            heuristique = new VariableNonAssigneeProviderRand();
            break;
        case MALIN:
            out << "c Choix des variables non assignées suivant leur fréquence d'apparition." << endl;
            heuristique = new VariableNonAssigneeProviderMalin();
            break;
        case MOMS:
            out << "c Choix des variables non assignées avec l'heuristique MOMS." << endl;
            heuristique = new VariableNonAssigneeProviderMOMS();
            break;
        case DLIS:
            out << "c Choix des variables non assignées avec l'heuristique DLIS." << endl;
            heuristique = new VariableNonAssigneeProviderDLIS();
            break;
        case SIMPLE:
        default:
            out << "c Choix des variables non assignées par défaut." << endl;
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

        if(utiliseCorrespondance)
        {
            for(auto e : correspondance)
                out<<e.first<<" "<<(formuleResolue.getVar(e.second)->getVal() ? e.second : -e.second)<<endl;

        }
        else
        {
            out << "s SATISFIABLE" << endl;
            for(int i = 1; i <= formuleResolue.getNombreDeVariables(); i++)
            {
                if(formuleResolue.getVar(i)->getVal())
                    out << "v " << i << endl;
                else
                    out << "v " << -i << endl;
            }
        }
    }
    else
    {
        out << "s UNSATISFIABLE" << endl;
    }
    delete solveur;

    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;

}

string LanceurSolveur::getFileName() const
{
    return fileName;
}

bool LanceurSolveur::isVerbose() const
{
    return verbose;
}
