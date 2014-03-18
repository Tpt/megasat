#include<iostream>
#include<cstdlib>
#include<cstring>
#include<chrono>
#include"include/Clause.h"
#include"include/Connecteurs.h"
#include"logique_parser/driver.h"

using namespace std;
using namespace std::chrono;

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
    string fileName = "";
    bool afficheFormule = false;

    afficheFormule=afficheFormule; ///A supprimer quand cette variable servira a quelque chose

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-o") == 0)
            afficheFormule = true;
        else
            fileName = argv[i];
    }

    if(fileName == "")
    {
        cerr << "c Pas de fichier donné en entrée.\nc Fin de la résolution." << endl;
        return EXIT_FAILURE;
    }
    try{
    FormuleTseitinSimple* formule = new FormuleTseitinSimple(parseFormuleFile(fileName));
    cout << formule->toString() << endl;
    cout << formule->toStringPrefix() << endl;
    cout << formule->toStringType() << endl;
    cout<< formule->getPOperandeG()->toString() << endl;
    cout<< formule->getPOperandeG()->toStringPrefix() << endl;
    cout<< formule->getPOperandeG()->toStringType() << endl;
    cout<< formule->getPOperandeG()->getPOperandeG()->toString() << endl;
    cout<< formule->getPOperandeG()->getPOperandeG()->toStringPrefix() << endl;
    cout<< formule->getPOperandeG()->getPOperandeG()->toStringType() << endl;
    cout << "Still alive !" << endl;
    delete formule;
    }
    catch(const FormuleTseitinSimpleError& e)
    {
        cout<<e.getMessage()<<endl;
    }
    return EXIT_SUCCESS;
}
