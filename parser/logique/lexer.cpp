#include "lexer.h"

namespace LogiqueParser {

Lexer::Lexer(std::istream* in, std::ostream* out)
: logiqueparserFlexLexer(in, out) {}

Lexer::~Lexer() {}

void Lexer::set_debug(bool b) {
    yy_flex_debug = b;
}

}

#ifdef yylex
#undef yylex
#endif

int logiqueparserFlexLexer::yylex() {
    std::cerr << "Unexpected call to calcparserFlexLexer::yylex()!" << std::endl;
    return 0;
}

int logiqueparserFlexLexer::yywrap() {
    return 1;
}
