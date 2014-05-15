#ifndef LEXER_H
#define LEXER_H

#ifndef YY_DECL
#define YY_DECL EgaliteParser::Parser::token_type \
    EgaliteParser::Lexer::yylex(EgaliteParser::Parser::semantic_type* yylval, EgaliteParser::Parser::location_type* yylloc)
#endif

#undef yyFlexLexer
#define yyFlexLexer EgaliteparserFlexLexer
#include <FlexLexer.h>

namespace EgaliteParser {
    class Driver;
}

#include "egaliteParser.hpp"

namespace EgaliteParser {
    class Lexer : public EgaliteparserFlexLexer {
    public:
        Lexer(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

        virtual ~Lexer();

        virtual Parser::token_type yylex(Parser::semantic_type *yylval, EgaliteParser::Parser::location_type* yylloc);

        void set_debug(bool b);
    };
}

#endif
