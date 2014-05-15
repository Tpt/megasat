#include<iostream>
#include"include/TransformationTseitin.h"
#include"include/LanceurSolveur.h"
#include"include/FormuleTseitin.h"
#include"parser/egalite/driver.h"
#include"include/InsatisfiableException.h"
#include"include/TheorieGreffonEgalite.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

FormuleTseitin<AtomeEgalite> parseFormuleFile(string fileName);

FormuleTseitin<AtomeEgalite> parseFormuleFile(string fileName)
{
    EgaliteParser::Driver parserDriver;
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
    
    FormuleTseitin<AtomeEgalite>* formuleTseitin = new FormuleTseitin<AtomeEgalite>(parseFormuleFile(arguments.getArgument("inputFile")));
    
    TransformationTseitin<AtomeEgalite> normalisateur(formuleTseitin);
    
    auto beginTime = system_clock::now();
    Formule formule(normalisateur.normaliser());
    formuleTseitin->free();
    delete formuleTseitin;
    
    try
    {
        TheorieGreffonEgalite theorieGreffon;
        vector<AtomeEgalite> correspondance(normalisateur.getCorrespondance().size());
        for(pair<AtomeEgalite, int> t : normalisateur.getCorrespondance())
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