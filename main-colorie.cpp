#include<iostream>
#include"include/ColParser.h"
#include"include/LanceurSolveur.h"
#include"include/CreateurContraintesColoriage.h"
#include"include/TransformationTseitin.h"
#include"include/InsatisfiableException.h"
#include"include/GraphvizOutput.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

Graphe parseColFile(string fileName);

Graphe parseColFile(string fileName)
{
    ColParser colParser;

    try
    {
        return colParser.parse(fileName);
    }
    catch(ParseError& e)
    {
        cerr << "c Erreur du parser : " << e.getMessage() << "\nc Arrêt de la résolution." << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    vector<string> nomArguments(2);
    nomArguments[0]="k";
    nomArguments[1]="inputFile";
    nomArguments[2]="outputFile";
    ArgumentsParser arguments(nomArguments, LanceurSolveur::getNomsOptions(), 2);
    arguments.parse(argc, argv);

    LanceurSolveur lanceur(arguments);
    ostream out(lanceur.getBufferSortie());

    Graphe graphe = parseColFile(arguments.getArgument("inputFile"));
    int k = atoi(arguments.getArgument("k").c_str());

    auto beginTime = system_clock::now();

    CreateurContraintesColoriage createurContraintes(graphe, k);
    FormuleTseitin* formuleTseitin = createurContraintes.cree();

    if(arguments.getOption("v"))
        formuleTseitin->print();

    TransformationTseitin normalisateur(formuleTseitin);

    Formule formule(normalisateur.normaliser());

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

    GraphvizOutput output(graphe, formule, normalisateur.getCorrespondance(), k);
    output.affiche(lanceur.getBufferSortie());

    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;

    return EXIT_SUCCESS;
}
