#ifndef CnfParser_H
#define CnfParser_H

#include<iostream>
#include"Formule.h"
#include"ParseError.h"

class CnfParser
{
public:
    //parse un fichier cnf contenu dans le flux istream ou un fichier
    Formule parse( std::string &fileName );
    Formule parse( std::istream &istream );

private:
    std::string getNextLine(std::istream &inputStream);
};

#endif
