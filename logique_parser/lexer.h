#ifndef LEXER_H
#define LEXER_H

#ifndef YY_DECL
#define YY_DECL LogiqueParser::Parser::token_type \
    LogiqueParser::Lexer::yylex(LogiqueParser::Parser::semantic_type* yylval, LogiqueParser::Parser::location_type* yylloc)
#endif

#undef yyFlexLexer
#define yyFlexLexer logiqueparserFlexLexer
#include <FlexLexer.h>

namespace LogiqueParser {
    class Driver;
}

#include "logiqueParser.hpp"

namespace LogiqueParser {
    class Lexer : public logiqueparserFlexLexer {
    public:
        Lexer(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

        virtual ~Lexer();

        virtual Parser::token_type yylex(Parser::semantic_type *yylval, LogiqueParser::Parser::location_type* yylloc);

        void set_debug(bool b);
    };
}

#endif
