%{

namespace LogiqueParser {
    class Driver;
}

#include <iostream>
#include <string>
#include "logiqueParser.hpp"
#include "lexer.h"
#include "driver.h"
#define yylex driver.lexer->yylex

%}

%union {
    std::string* d;
}

%type <d> Expression

%token TEOF 0
%token  <d> ID
%token  ET OU IMPLIQUE NON
%token  PARENTHESE_GAUCHE PARENTHESE_DROITE

%left IMPLIQUE
%left ET
%left OU
%left NON

%start Input

%language "C++"
%define namespace "LogiqueParser"
%define parser_class_name "Parser"
%parse-param {Driver &driver}

%error-verbose

%%

Input:
Expression TEOF
{
    std::cout << "Resultat : " << *$1 << std::endl;  /* Ici le "programme principal"
                                                     est ridicule; "en vrai", on
                                                     stockerait en mémoire l'entrée
                                                     que l'on a reconnue (par exemple
                                                     une clause) */
}
;

Expression:
ID {$$=$1; }
| Expression IMPLIQUE Expression { $$=new std::string(*$1+*$3); }
| Expression ET Expression { $$=new std::string(*$1+*$3); }
| Expression OU Expression { $$=new std::string(*$1+*$3); }
| NON Expression { $$=$2; }
| PARENTHESE_GAUCHE Expression PARENTHESE_DROITE { $$=$2; }
;


%%

void LogiqueParser::Parser::error(const std::string& m)
{
    std::cerr << m << std::endl;
}
