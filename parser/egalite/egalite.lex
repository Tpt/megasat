%option yylineno
%option c++
%option prefix="EgaliteParser"

%{

namespace  EgaliteParser {
    class Driver;
}

#include "egaliteParser.hpp"
#include "lexer.h"
typedef EgaliteParser::Parser::token token;
typedef EgaliteParser::Parser::token_type token_type;
#define yyterminate() return token::TEOF

%}


blancs  [ \t\n]+
entier  [0-9]+

%%

{blancs}  { /* On ignore */}

"/\\"   return(token::ET);
"\\/"   return(token::OU);
"=>"    return(token::IMPLIQUE);
"~"     return(token::NON);
"x"     return(token::X);
"="     return(token::EQ);
"!="    return(token::NEQ);

{entier}  {
  yylval->entier = atoi(yytext);
  return(token::ID);
}

"("     return(token::PARENTHESE_GAUCHE);
")"     return(token::PARENTHESE_DROITE);
