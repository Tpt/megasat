#include<cstdlib>
#include<cstring>
#include<ctime>
#include"include/Formule.h"
#include"include/CnfParser.h"
#include"include/DavisPutnamSolveur.h"
#include"include/DPLLSolveur.h"

using namespace std;
Formule parseCnfFile(string fileName);

Formule parseCnfFile(string fileName)
{
    CnfParser cnfParser;

    try
    {
        return cnfParser.parse(fileName);
    }
    catch(ParseError)
    {
        cerr << "resol: fatal error: parser error\nresolution terminated." << endl << endl;
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

    clock_t t;
    t = clock();
    bool estSatisfiable = false;

    if(utiliserDavisPutnam)
    {
        DavisPutnamSolveur solveur(formule);
        estSatisfiable = solveur.isSatifiable();
        formule = solveur.getFomule();
    }
    else
    {
        DPLLSolveur solveur(formule, avecLiterauxSurveilles);
        estSatisfiable = solveur.isSatifiable();
        formule = solveur.getFomule();
    }

    if(estSatisfiable)
    {
        cout << "s SATISFIABLE" << endl;
        for(int i = 0; i < formule.getNombreDeVariables(); i++)
        {
            if(formule.getVar(i)->getVal())
                cout << "v " << i + 1 << endl;
            else
                cout << "v " << -i -1 << endl;
        }
    }
    else
    {
        cout << "s UNSATISFIABLE" << endl;
    }
    t = clock() - t;
    cout << "c Resolu en : " << static_cast<double>(t) / static_cast<double>(CLOCKS_PER_SEC) << " secondes" << endl;

    return EXIT_SUCCESS;
}
