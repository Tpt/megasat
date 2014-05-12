%option yylineno
%option c++
%option prefix="CongruenceParser"

%{

namespace  CongruenceParser {
    class Driver;
}

#include "congruenceParser.hpp"
#include "lexer.h"
typedef CongruenceParser::Parser::token token;
typedef CongruenceParser::Parser::token_type token_type;
#define yyterminate() return token::TEOF

%}


blancs  [ \t\n]+
entier  [0-9]+
chars    [a-z]+

%%

{blancs}  { /* On ignore */}

"/\\"   return(token::ET);
"\\/"   return(token::OU);
"=>"    return(token::IMPLIQUE);
"~"     return(token::NON);
"x"     return(token::X);
","     return(token::VIRGULE);
"="     return(token::EQ);
"!="    return(token::NEQ);

{entier}  {
  yylval->entier = atoi(yytext);
  return(token::ID);
}

{chars}  {
  yylval->str = new std::string(yytext);
  return(token::SYMBOLE);
}

"("     return(token::PARENTHESE_GAUCHE);
")"     return(token::PARENTHESE_DROITE);
