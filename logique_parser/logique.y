%code requires {
    #include "../include/Connecteurs.h"
}

%{

namespace LogiqueParser {
    class Driver;
}

#include <sstream>
#include "logiqueParser.hpp"
#include "lexer.h"
#include "driver.h"
#include "../include/ParseError.h"
#define yylex driver.lexer->yylex
%}

%union
{
    std::string* d;
    FormuleTseitinSimple* formule;
}

%type <formule> Expression

%token TEOF 0
%token  <d> ID
%token  ET OU IMPLIQUE NON
%token  PARENTHESE_GAUCHE PARENTHESE_DROITE

%left IMPLIQUE
%left OU
%left ET
%left NON

%start Input

%language "C++"
%define namespace "LogiqueParser"
%define parser_class_name "Parser"
%parse-param {Driver &driver}
%locations

%error-verbose

%%

Input:
Expression TEOF
{
    driver.setResult(*$1);
}
;

Expression:
ID { $$=new FormuleTseitinSimple(FormuleTseitinSimple::VARIABLE, *$1); }
| Expression IMPLIQUE Expression { $$ = new FormuleTseitinSimple(FormuleTseitinSimple::IMPLIQUE, $1, $3); }
| Expression ET Expression { $$ = new FormuleTseitinSimple(FormuleTseitinSimple::ET, $1, $3); }
| Expression OU Expression { $$ = new FormuleTseitinSimple(FormuleTseitinSimple::OU, $1, $3); }
| NON Expression { $$ = new FormuleTseitinSimple(FormuleTseitinSimple::NON, $2); }
| PARENTHESE_GAUCHE Expression PARENTHESE_DROITE { $$=$2; }
;


%%

void LogiqueParser::Parser::error(const location_type& loc, const std::string& m)
{
    int location = loc.begin.line;
    std::ostringstream out;
    out << "Ligne " << location << " : " << m;
    throw ParseError(out.str());
}
