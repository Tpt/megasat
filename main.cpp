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
int Clause::nextUid=0;

Formule parseCnfFile(string fileName)
{
    CnfParser cnfParser;

    try
    {
        return cnfParser.parse(fileName);
    }
    catch(ParseError& e)
    {
        cerr << "resol: fatal error: parser error: " << e.getMessage() << "\nresolution terminated." << endl << endl;
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
        cerr << "resol: fatal error: no input files\nresolution terminated." << endl << endl;
        return EXIT_FAILURE;
    }

    Formule formule = parseCnfFile(fileName);

    auto beginTime = steady_clock::now();
    bool estSatisfiable = false;

    if(utiliserDavisPutnam)
    {
        DavisPutnamSolveur solveur(formule);
        estSatisfiable = solveur.isSatifiable();
        formule = solveur.getFomule();
    }
    else if(avecLiterauxSurveilles)
    {
        DPLLSurveilleSolveur solveur(formule);
        estSatisfiable = solveur.isSatifiable();
        formule = solveur.getFomule();
    }
    else
    {
        DPLLSolveur solveur(formule);
        estSatisfiable = solveur.isSatifiable();
        formule = solveur.getFomule();
    }

    if(estSatisfiable)
    {
        cout << "s SATISFIABLE" << endl;
        for(int i = 1; i <= formule.getNombreDeVariables(); i++)
        {
            if(formule.getVar(i)->getVal())
                cout << "v " << i << endl;
            else
                cout << "v " << -i << endl;
        }
    }
    else
    {
        cout << "s UNSATISFIABLE" << endl;
    }
    cout << "c Resolu en : " << duration_cast<duration<double>>(steady_clock::now() - beginTime).count() << " secondes" << endl;

    return EXIT_SUCCESS;
}
