#ifndef CnfParser_H
#define CnfParser_H

#include<iostream>
#include"Formule.h"

class CnfParser
{
public:
	//parse un fichier cnf contenu dans le flux istream ou un fichier
    Formule parse( std::string &fileName );
	Formule parse( std::istream &istream );
};

class ParseError: std::exception
{};

#endif