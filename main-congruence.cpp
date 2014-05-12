#include<iostream>
#include"include/TransformationTseitin.h"
#include"include/LanceurSolveur.h"
#include"include/FormuleTseitin.h"
#include"parser/congruence/driver.h"
#include"include/InsatisfiableException.h"
#include"include/TheorieGreffonCongruence.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

FormuleTseitin<AtomeCongruence> parseFormuleFile(string fileName);

FormuleTseitin<AtomeCongruence> parseFormuleFile(string fileName)
{
    CongruenceParser::Driver parserDriver;
    try
    {
        return parserDriver.parse(fileName);
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
    nomArguments[0]="inputFile";
    ArgumentsParser arguments(nomArguments, LanceurSolveur::getNomsOptions(), 1);
    arguments.parse(argc, argv);

    LanceurSolveur lanceur(arguments, "c");
    ostream out(lanceur.getBufferSortie());

    FormuleTseitin<AtomeCongruence>* formuleTseitin = new FormuleTseitin<AtomeCongruence>(parseFormuleFile(arguments.getArgument("inputFile")));

    TransformationTseitin<AtomeCongruence> normalisateur(formuleTseitin);

    auto beginTime = system_clock::now();
    Formule formule(normalisateur.normaliser());
    formuleTseitin->free();
    delete formuleTseitin;

    try
    {
        TheorieGreffonCongruence theorieGreffon;
        formule = lanceur.execute(formule, theorieGreffon);
    }
    catch(InsatisfiableException)
    {
        out << "s UNSATISFIABLE" << endl;
    }
    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;
    
    
    return EXIT_SUCCESS;
}