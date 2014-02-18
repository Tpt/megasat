#include<cstdlib>
#include<ctime>
#include"include/Formule.h"
#include"include/CnfParser.h"
#include"include/DavisPutnamSolveur.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        cerr << "resol: fatal error: no input files\nresolution terminated." << endl << endl;
        return EXIT_FAILURE;
    }

    CnfParser cnfParser;
    Formule formule;
    string fileName = argv[1];
    try
    {
        formule = cnfParser.parse(fileName);
    }
    catch(ParseError)
    {
        cerr << "resol: fatal error: parser error\nresolution terminated." << endl << endl;
        return EXIT_FAILURE;
    }

    clock_t t;
    t = clock();
    DavisPutnamSolveur solveur( formule );
    if( solveur.isSatifiable() ) {
        cout << "s SATISFIABLE" << endl;
        /*for(int i = 0; i < formule.getVariableNumber(); i++)
        {
            if(vars[i]->getVal())
                cout << "v " << i + 1 << endl;
            else
                cout <<"v " << -i -1 << endl;
        }*/
    }
    else
    {
        cout<<"s UNSATISFIABLE"<<endl;
    }
    t = clock() - t;
    cout << "c Resolu en : " << static_cast<double>(t) / static_cast<double>(CLOCKS_PER_SEC) << " secondes" << endl;

    return EXIT_SUCCESS;
}
    