#ifndef LEXER_H
#define LEXER_H

#ifndef YY_DECL
#define YY_DECL CongruenceParser::Parser::token_type \
    CongruenceParser::Lexer::yylex(CongruenceParser::Parser::semantic_type* yylval, CongruenceParser::Parser::location_type* yylloc)
#endif

#undef yyFlexLexer
#define yyFlexLexer CongruenceparserFlexLexer
#include <FlexLexer.h>

namespace CongruenceParser {
    class Driver;
}

#include "CongruenceParser.hpp"

namespace CongruenceParser {
    class Lexer : public CongruenceparserFlexLexer {
    public:
        Lexer(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

        virtual ~Lexer();

        virtual Parser::token_type yylex(Parser::semantic_type *yylval, CongruenceParser::Parser::location_type* yylloc);

        void set_debug(bool b);
    };
}

#endif
