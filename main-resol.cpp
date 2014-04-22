#include"include/LanceurSolveur.h"
#include"include/Formule.h"
#include"include/CnfParser.h"
#include"include/InsatisfiableException.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

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
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    vector<string> nomArguments(1);
    nomArguments[0] = "inputFile";
    ArgumentsParser arguments(nomArguments, LanceurSolveur::getNomsOptions(), 1);
    arguments.parse(argc, argv);

    LanceurSolveur lanceur(arguments, "c");

    Formule formule = parseCnfFile(arguments.getArgument("inputFile"));
    ostream out(lanceur.getBufferSortie());

    auto beginTime = system_clock::now();
    try
    {
        formule = lanceur.execute(formule);

        out << "s SATISFIABLE" << endl;
        for(int i = 1; i <= formule.getNombreDeVariables(); i++)
        {
            if(formule.getVar(i)->getVal())
                out << "v " << i << endl;
            else
                out << "v " << -i << endl;
        }
    }
    catch(InsatisfiableException)
    {
        out << "s UNSATISFIABLE" << endl;
    }
    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;

    return EXIT_SUCCESS;
}
