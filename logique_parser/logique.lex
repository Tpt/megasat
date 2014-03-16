%option yylineno
%option c++
%option prefix="LogiqueParser"

%{

namespace  LogiqueParser {
    class Driver;
}

#include "logiqueParser.hpp"
#include "lexer.h"
typedef LogiqueParser::Parser::token token;
typedef LogiqueParser::Parser::token_type token_type;
#define yyterminate() return token::TEOF

%}


blancs    [ \t\n]+
chars     [a-z]+

%%

{blancs}  { /* On ignore */}


{chars}  {
  yylval->d=new std::string(yytext);
  return(token::ID);
}


"/\\"   return(token::ET);
"\\/"   return(token::OU);
"=>"   return(token::IMPLIQUE);
"~"   return(token::NON);

"("   return(token::PARENTHESE_GAUCHE);
")"   return(token::PARENTHESE_DROITE);
