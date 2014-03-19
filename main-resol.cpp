#include<cstdlib>
#include<cstring>
#include"include/LanceurSolveur.h"
#include"include/Formule.h"
#include"include/CnfParser.h"

using namespace std;
Formule parseCnfFile(string fileName);

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
    LanceurSolveur lanceur;

    lanceur.parseOptions(argc, argv);

    Formule formule = parseCnfFile(lanceur.getFileName());

    lanceur.ExecuteEtAfficheResultat(formule);

    return EXIT_SUCCESS;
}
