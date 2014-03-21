#include<iostream>
#include"include/ColParser.h"
#include"include/LanceurSolveur.h"

using namespace std;
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
        exit( EXIT_FAILURE );
    }
}

int main(int argc, char *argv[])
{

    LanceurSolveur lanceur;

    lanceur.parseOptions(argc, argv);

    Graphe graphe = parseColFile(lanceur.getFileName());

    return EXIT_SUCCESS;
}
