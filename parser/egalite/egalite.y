%code requires {
    #include "../../include/FormuleTseitin.h"
    #include "../../include/AtomeEgalite.h"
}

%{

namespace EgaliteParser {
    class Driver;
}

#include <sstream>
#include "egaliteParser.hpp"
#include "lexer.h"
#include "driver.h"
#include "../../include/ParseError.h"
#define yylex driver.lexer->yylex
%}

%union
{
    std::string* str;
    int entier;
    FormuleTseitin<AtomeEgalite>* formule;
}

%type <formule> Expression

%token TEOF 0
%token <entier> ID
%token ET OU IMPLIQUE NON EQ NEQ X
%token PARENTHESE_GAUCHE PARENTHESE_DROITE

%left IMPLIQUE
%left OU
%left ET
%left NON
%left EQ NEQ

%start Input

%language "C++"
%define namespace "EgaliteParser"
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
X ID NEQ X ID { $$ = new FormuleTseitin<AtomeEgalite>(FormuleTseitin<AtomeEgalite>::NON, new FormuleTseitin<AtomeEgalite>(FormuleTseitin<AtomeEgalite>::VARIABLE, AtomeEgalite($2, $5))); }
| X ID EQ X ID { $$ = new FormuleTseitin<AtomeEgalite>(FormuleTseitin<AtomeEgalite>::VARIABLE, AtomeEgalite($2, $5)); }
| Expression IMPLIQUE Expression { $$ = new FormuleTseitin<AtomeEgalite>(FormuleTseitin<AtomeEgalite>::IMPLIQUE, $1, $3); }
| Expression ET Expression { $$ = new FormuleTseitin<AtomeEgalite>(FormuleTseitin<AtomeEgalite>::ET, $1, $3); }
| Expression OU Expression { $$ = new FormuleTseitin<AtomeEgalite>(FormuleTseitin<AtomeEgalite>::OU, $1, $3); }
| NON Expression { $$ = new FormuleTseitin<AtomeEgalite>(FormuleTseitin<AtomeEgalite>::NON, $2); }
| PARENTHESE_GAUCHE Expression PARENTHESE_DROITE { $$=$2; }
;

%%

void EgaliteParser::Parser::error(const location_type& loc, const std::string& m)
{
    int location = loc.begin.line;
    std::ostringstream out;
    out << "Ligne " << location << " : " << m;
    throw ParseError(out.str());
}
