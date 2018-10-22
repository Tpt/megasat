#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include "../../include/FormuleTseitin.h"
#include "../../include/ParseError.h"

namespace LogiqueParser
{

class Parser;
class Lexer;

class Driver
{
public:
    Driver();
    ~Driver();

    FormuleTseitin<std::string> parse(std::string& fileName);
    FormuleTseitin<std::string> parse(std::istream& inputStream);

    void setResult(FormuleTseitin<std::string>& result);
private:
    Lexer* lexer;
    Parser* parser;
    FormuleTseitin<std::string> result;

    friend class Parser;
    friend class Lexer;
};

}

#endif // DRIVER_H
