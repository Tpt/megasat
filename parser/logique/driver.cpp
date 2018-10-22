#include <fstream>

#include "driver.h"
#include "lexer.h"

using namespace std;

namespace LogiqueParser {

Driver::Driver() : lexer(new Lexer()), parser(new Parser(*this)), result(FormuleTseitin<std::string>())
{}

Driver::~Driver()
{
    delete parser;
    delete lexer;
}

void Driver::setResult(FormuleTseitin<std::string>& _result)
{
    result = _result;
}

FormuleTseitin<std::string> Driver::parse(istream& inputStream)
{
    lexer->switch_streams(&inputStream, &cerr);

    if (parser->parse() != 0) {
        throw ParseError("Parser error");
    }

    return result;
}

FormuleTseitin<std::string> Driver::parse(std::string& fileName)
{
    filebuf fb;
    fb.open(fileName, std::ios::in);
    istream is(&fb);
    return this->parse(is);
}
}
