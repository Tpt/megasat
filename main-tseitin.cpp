#include<iostream>
#include"include/TransformationTseitin.h"
#include"include/LanceurSolveur.h"
#include"include/Connecteurs.h"
#include"logique_parser/driver.h"

using namespace std;

FormuleTseitinSimple parseFormuleFile(string fileName);

FormuleTseitinSimple parseFormuleFile(string fileName)
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

    FormuleTseitinSimple* formuleTseitin = new FormuleTseitinSimple(parseFormuleFile(lanceur.getFileName()));

    TransformationTseitin normalisateur(formuleTseitin);

    Formule formule(normalisateur.normaliser());

    if(lanceur.isVerbose())
        formule.print();

    lanceur.utiliserCorrespondance(normalisateur.getCorrespondance());

    lanceur.ExecuteEtAfficheResultat(formule);


    return EXIT_SUCCESS;
}
