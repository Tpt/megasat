%option yylineno
%option c++
%option prefix="DifferenceParser"

%{

namespace  DifferenceParser {
    class Driver;
}

#include "differenceParser.hpp"
#include "lexer.h"
typedef DifferenceParser::Parser::token token;
typedef DifferenceParser::Parser::token_type token_type;
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
"-"     return(token::MOINS);
"="     return(token::EQ);
"!="    return(token::NEQ);
"<"    return(token::L);
"<="    return(token::LEQ);
">"    return(token::G);
">="    return(token::GEQ);

{entier}  {
  yylval->entier = atoi(yytext);
  return(token::ID);
}

"("     return(token::PARENTHESE_GAUCHE);
")"     return(token::PARENTHESE_DROITE);
