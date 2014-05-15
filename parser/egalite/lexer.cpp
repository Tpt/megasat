#include "lexer.h"

namespace EgaliteParser {

Lexer::Lexer(std::istream* in, std::ostream* out)
: EgaliteparserFlexLexer(in, out) {}

Lexer::~Lexer() {}

void Lexer::set_debug(bool b) {
    yy_flex_debug = b;
}

}

#ifdef yylex
#undef yylex
#endif

int EgaliteparserFlexLexer::yylex() {
    std::cerr << "Unexpected call to calcparserFlexLexer::yylex()!" << std::endl;
    return 0;
}

int EgaliteparserFlexLexer::yywrap() {
    return 1;
}
