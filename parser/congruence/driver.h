#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include "../../include/FormuleTseitin.h"
#include "../../include/AtomeCongruence.h"
#include "../../include/ParseError.h"

namespace CongruenceParser
{

class Parser;
class Lexer;

class Driver
{
public:
    Driver();
    Driver(const Driver& other);
    Driver& operator= (const Driver& other);
    ~Driver();

    FormuleTseitin<AtomeCongruence> parse(std::string& fileName);
    FormuleTseitin<AtomeCongruence> parse(std::istream& inputStream);

    void setResult(FormuleTseitin<AtomeCongruence>& result);
private:
    Lexer* lexer;
    Parser* parser;
    FormuleTseitin<AtomeCongruence> result;

    friend class Parser;
    friend class Lexer;
};

}

#endif // DRIVER_H
