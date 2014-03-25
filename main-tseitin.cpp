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

    LanceurSolveur lanceur;

    lanceur.parseOptions(argc, argv);
    ostream out(lanceur.getBufferSortie());

    FormuleTseitin* formuleTseitin = new FormuleTseitin(parseFormuleFile(lanceur.getFileName()));

    TransformationTseitin normalisateur(formuleTseitin);

    auto beginTime = system_clock::now();
    Formule formule(normalisateur.normaliser());

    if(lanceur.isVerbose())
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
