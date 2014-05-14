#include<iostream>
#include"include/TransformationTseitin.h"
#include"include/LanceurSolveur.h"
#include"include/FormuleTseitin.h"
#include"parser/difference/driver.h"
#include"include/InsatisfiableException.h"
#include"include/TheorieGreffonDifference.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

FormuleTseitin<AtomeDifference> parseFormuleFile(string fileName);

FormuleTseitin<AtomeDifference> parseFormuleFile(string fileName)
{
    DifferenceParser::Driver parserDriver;
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
    
    FormuleTseitin<AtomeDifference>* formuleTseitin = new FormuleTseitin<AtomeDifference>(parseFormuleFile(arguments.getArgument("inputFile")));
    
    TransformationTseitin<AtomeDifference> normalisateur(formuleTseitin);
    
    auto beginTime = system_clock::now();
    Formule formule(normalisateur.normaliser());
    formuleTseitin->free();
    delete formuleTseitin;
    
    try
    {
        TheorieGreffonDifference theorieGreffon;
        vector<AtomeDifference> correspondance(normalisateur.getCorrespondance().size());
        for(pair<AtomeDifference, int> t : normalisateur.getCorrespondance())
            correspondance[static_cast<size_t>(t.second - 1)]=t.first;
        
        theorieGreffon.setCorrespondanceAtomes(correspondance);
        
        formule = lanceur.execute(formule, theorieGreffon);

        out << "s SATISFIABLE" << endl;
    }
    catch(InsatisfiableException)
    {
        out << "s UNSATISFIABLE" << endl;
    }
    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;
    
    
    return EXIT_SUCCESS;
}