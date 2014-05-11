%code requires {
    #include "../../include/FormuleTseitin.h"
    #include "../../include/AtomeCongruence.h"
}

%{

namespace CongruenceParser {
    class Driver;
}

#include <sstream>
#include "congruenceParser.hpp"
#include "lexer.h"
#include "driver.h"
#include "../../include/ParseError.h"
#define yylex driver.lexer->yylex
%}

%union
{
    std::string* str;
    int entier;
    FormuleTseitin<AtomeCongruence>* formule;
    AtomeCongruence* atome;
    Terme* terme;
    vector<Terme*>* arguments;
}

%type <formule> Expression
%type <atome> Atome
%type <terme> Formule
%type <arguments> ListeArguments

%token TEOF 0
%token <entier> ID
%token <str> SYMBOLE
%token VIRGULE
%token ET OU IMPLIQUE NON EGALS X
%token PARENTHESE_GAUCHE PARENTHESE_DROITE

%left IMPLIQUE
%left OU
%left ET
%left NON
%left EGALS

%start Input

%language "C++"
%define namespace "CongruenceParser"
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
Atome { $$ = new FormuleTseitin<AtomeCongruence>(FormuleTseitin<AtomeCongruence>::VARIABLE, *$1); }
| Expression IMPLIQUE Expression { $$ = new FormuleTseitin<AtomeCongruence>(FormuleTseitin<AtomeCongruence>::IMPLIQUE, $1, $3); }
| Expression ET Expression { $$ = new FormuleTseitin<AtomeCongruence>(FormuleTseitin<AtomeCongruence>::ET, $1, $3); }
| Expression OU Expression { $$ = new FormuleTseitin<AtomeCongruence>(FormuleTseitin<AtomeCongruence>::OU, $1, $3); }
| NON Expression { $$ = new FormuleTseitin<AtomeCongruence>(FormuleTseitin<AtomeCongruence>::NON, $2); }
| PARENTHESE_GAUCHE Expression PARENTHESE_DROITE { $$=$2; }
;

Atome:
Formule EGALS Formule { $$ = new AtomeCongruence(*$1, *$3); }
;

Formule:
X ID { $$ = new Terme($2); }
| SYMBOLE PARENTHESE_GAUCHE PARENTHESE_DROITE { $$ = new Terme( *$1, vector<Terme*>(0) ); }
| SYMBOLE PARENTHESE_GAUCHE ListeArguments PARENTHESE_DROITE { $$ = new Terme(*$1, *$3); }
;

ListeArguments:
Formule { $$ = new vector<Terme*>(); $$->push_back($1); }
| ListeArguments VIRGULE Formule { $1->push_back($3); $$ = $1; }
;

%%

void CongruenceParser::Parser::error(const location_type& loc, const std::string& m)
{
    int location = loc.begin.line;
    std::ostringstream out;
    out << "Ligne " << location << " : " << m;
    throw ParseError(out.str());
}
