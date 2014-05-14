%code requires {
    #include "../../include/FormuleTseitin.h"
    #include "../../include/AtomeDifference.h"
}

%{

namespace DifferenceParser {
    class Driver;
}

#include <sstream>
#include "differenceParser.hpp"
#include "lexer.h"
#include "driver.h"
#include "../../include/ParseError.h"
#define yylex driver.lexer->yylex
%}

%union
{
    std::string* str;
    int entier;
    FormuleTseitin<AtomeDifference>* formule;
}

%type <formule> Expression
%type <entier> Entier

%token TEOF 0
%token <entier> ID
%token ET OU IMPLIQUE NON EQ NEQ L LEQ G GEQ X MOINS
%token PARENTHESE_GAUCHE PARENTHESE_DROITE

%left IMPLIQUE
%left OU
%left ET
%left NON
%left EQ NEQ L LEQ G GEQ

%start Input

%language "C++"
%define namespace "DifferenceParser"
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
X ID EQ Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::ET,
    (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($2 + 1, 0, $4))),
    (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference(0, $2 + 1, -$4)))
    ); }
| X ID NEQ Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::NON,
    (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::ET,
        (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($2 + 1, 0, $4))),
        (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference(0, $2 + 1, -$4)))
    ))); }
| X ID L Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($2 + 1, 0, $4 - 1)); }
| X ID LEQ Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($2 + 1, 0, $4)); }
| X ID G Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference(0, $2 + 1, -$4 - 1)); }
| X ID GEQ Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference(0, $2 + 1, -$4)); }

| X ID MOINS X ID EQ Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::ET,
    (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($2 + 1, $5 + 1, $7))),
    (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($5 + 1, $2 + 1, -$7)))
    ); }
| X ID MOINS X ID NEQ Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::NON,
    (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::ET,
    (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($2 + 1, $5 + 1, $7))),
    (new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($5 + 1, $2 + 1, -$7)))
    ))); }
| X ID MOINS X ID LEQ Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($2 + 1, $5 + 1, $7)); }
| X ID MOINS X ID L Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($2 + 1, $5 + 1, $7 - 1)); }
| X ID MOINS X ID GEQ Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($5 + 1, $2 + 1, -$7)); }
| X ID MOINS X ID G Entier { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::VARIABLE, AtomeDifference($5 + 1, $2 + 1, -$7 - 1)); }

| Expression IMPLIQUE Expression { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::IMPLIQUE, $1, $3); }
| Expression ET Expression { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::ET, $1, $3); }
| Expression OU Expression { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::OU, $1, $3); }
| NON Expression { $$ = new FormuleTseitin<AtomeDifference>(FormuleTseitin<AtomeDifference>::NON, $2); }
| PARENTHESE_GAUCHE Expression PARENTHESE_DROITE { $$=$2; }
;

Entier:
MOINS ID { $$ = -$2; }
| ID { $$ = $1; }
%%

void DifferenceParser::Parser::error(const location_type& loc, const std::string& m)
{
    int location = loc.begin.line;
    std::ostringstream out;
    out << "Ligne " << location << " : " << m;
    throw ParseError(out.str());
}
