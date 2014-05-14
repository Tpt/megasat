#ifndef LEXER_H
#define LEXER_H

#ifndef YY_DECL
#define YY_DECL DifferenceParser::Parser::token_type \
    DifferenceParser::Lexer::yylex(DifferenceParser::Parser::semantic_type* yylval, DifferenceParser::Parser::location_type* yylloc)
#endif

#undef yyFlexLexer
#define yyFlexLexer DifferenceparserFlexLexer
#include <FlexLexer.h>

namespace DifferenceParser {
    class Driver;
}

#include "differenceParser.hpp"

namespace DifferenceParser {
    class Lexer : public DifferenceparserFlexLexer {
    public:
        Lexer(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

        virtual ~Lexer();

        virtual Parser::token_type yylex(Parser::semantic_type *yylval, DifferenceParser::Parser::location_type* yylloc);

        void set_debug(bool b);
    };
}

#endif
