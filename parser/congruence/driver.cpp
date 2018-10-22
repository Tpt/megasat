#include <fstream>

#include "driver.h"
#include "lexer.h"

using namespace std;

namespace CongruenceParser {

Driver::Driver() : lexer(new Lexer()), parser(new Parser(*this)), result(FormuleTseitin<AtomeCongruence>())
{}

Driver::~Driver()
{
    delete parser;
    delete lexer;
}

void Driver::setResult(FormuleTseitin<AtomeCongruence>& _result)
{
    result = _result;
}

FormuleTseitin<AtomeCongruence> Driver::parse(istream& inputStream)
{
    lexer->switch_streams(&inputStream, &cerr);

    if (parser->parse() != 0) {
        throw ParseError("Parser error");
    }

    return result;
}

FormuleTseitin<AtomeCongruence> Driver::parse(std::string& fileName)
{
    filebuf fb;
    fb.open(fileName, std::ios::in);
    istream is(&fb);
    return this->parse(is);
}
}
