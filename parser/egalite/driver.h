#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include "../../include/FormuleTseitin.h"
#include "../../include/AtomeEgalite.h"
#include "../../include/ParseError.h"

namespace EgaliteParser
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

    FormuleTseitin<AtomeEgalite> parse(std::string& fileName);
    FormuleTseitin<AtomeEgalite> parse(std::istream& inputStream);

    void setResult(FormuleTseitin<AtomeEgalite>& result);
private:
    Lexer* lexer;
    Parser* parser;
    FormuleTseitin<AtomeEgalite> result;

    friend class Parser;
    friend class Lexer;
};

}

#endif // DRIVER_H
