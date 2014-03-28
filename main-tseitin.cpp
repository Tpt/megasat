#include<iostream>
#include"include/TransformationTseitin.h"
#include"include/LanceurSolveur.h"
#include"include/FormuleTseitin.h"
#include"logique_parser/driver.h"
#include"include/InsatisfiableException.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

FormuleTseitin parseFormuleFile(string fileName);

FormuleTseitin parseFormuleFile(string fileName)
{
    LogiqueParser::Driver parserDriver;
    try
    {
        return parserDriver.parse(fileName);
    }
    catch(ParseError& e)
    {
        cerr << "c Erreur du parser : " << e.getMessage() << "\nc Arrêt de la résolution." << endl;
        exit( EXIT_FAILURE );
    }
}

int main(int argc, char *argv[])
{
    vector<string> nomArguments = {"inputFile", "outputFile"};
    ArgumentsParser arguments(nomArguments, LanceurSolveur::getNomsOptions(), 1);
    arguments.parse(argc, argv);

    LanceurSolveur lanceur(arguments);
    ostream out(lanceur.getBufferSortie());

    FormuleTseitin* formuleTseitin = new FormuleTseitin(parseFormuleFile(arguments.getArgument("inputFile")));

    TransformationTseitin normalisateur(formuleTseitin);

    auto beginTime = system_clock::now();
    Formule formule(normalisateur.normaliser());

    if(arguments.getOption("v"))
        formule.print();

    try
    {
        formule = lanceur.execute(formule);
        
        for(auto e : normalisateur.getCorrespondance())
            out << e.first << " " << (formule.getVar(e.second)->getVal() ? e.second : -e.second) << endl;
    }
    catch(InsatisfiableException)
    {
        out << "s UNSATISFIABLE" << endl;
    }
    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;


    return EXIT_SUCCESS;
}
