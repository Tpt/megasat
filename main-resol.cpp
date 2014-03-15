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

Formule parseCnfFile(string fileName);
int Clause::nextUid = 0;

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

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-wl") == 0)
            avecLiterauxSurveilles = true;
        else if(strcmp(argv[i], "-dp") == 0)
            utiliserDavisPutnam = true;
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

    Solveur* solveur = nullptr;
    if(utiliserDavisPutnam)
    {
        solveur = new DavisPutnamSolveur(formule);
    }
    else if(avecLiterauxSurveilles)
    {
        solveur = new DPLLSurveilleSolveur(formule);
    }
    else
    {
        solveur = new DPLLSolveur(formule);
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
