#include<cstdlib>
#include<ctime>
#include <getopt.h>
#include"include/Formule.h"
#include"include/CnfParser.h"
#include"include/DavisPutnamSolveur.h"

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

    static struct option longOptions[] = {
        {"wl", no_argument, 0, 'w'},
        {0, 0, 0, 0}
    };
    int optionIndex = 0, c;
    while((c = getopt_long (argc, argv, "w", longOptions, &optionIndex)) != -1)
    {
        switch(c)
        {
            case 'w':
                avecLiterauxSurveilles = true;
                break;
            default:
                break;
        }
    }
    if(optind < argc)
    {
        fileName = argv[optind];
    }

    avecLiterauxSurveilles=avecLiterauxSurveilles;//TODO grotesque

    if(fileName == "")
    {
        cerr << "resol: fatal error: no input files\nresolution terminated." << endl << endl;
        return EXIT_FAILURE;
    }

    Formule formule = parseCnfFile(argv[1]);

    clock_t t;
    t = clock();
    DavisPutnamSolveur solveur( formule );
    if( solveur.isSatifiable() ) {
        formule = solveur.getFomule();
        cout << "s SATISFIABLE" << endl;
        for(int i = 0; i < formule.getNombreDeVariables(); i++)
        {
            if( formule.getVar(i)->getVal())
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
