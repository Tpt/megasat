%code requires {
    #include "../include/FormuleTseitin.h"
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
    FormuleTseitin* formule;
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
ID { $$=new FormuleTseitin(FormuleTseitin::VARIABLE, *$1); }
| Expression IMPLIQUE Expression { $$ = new FormuleTseitin(FormuleTseitin::IMPLIQUE, $1, $3); }
| Expression ET Expression { $$ = new FormuleTseitin(FormuleTseitin::ET, $1, $3); }
| Expression OU Expression { $$ = new FormuleTseitin(FormuleTseitin::OU, $1, $3); }
| NON Expression { $$ = new FormuleTseitin(FormuleTseitin::NON, $2); }
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
