#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include "../../include/FormuleTseitin.h"
#include "../../include/AtomeDifference.h"
#include "../../include/ParseError.h"

namespace DifferenceParser
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

    FormuleTseitin<AtomeDifference> parse(std::string& fileName);
    FormuleTseitin<AtomeDifference> parse(std::istream& inputStream);

    void setResult(FormuleTseitin<AtomeDifference>& result);
private:
    Lexer* lexer;
    Parser* parser;
    FormuleTseitin<AtomeDifference> result;

    friend class Parser;
    friend class Lexer;
};

}

#endif // DRIVER_H
