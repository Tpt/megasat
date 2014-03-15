#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include "../include/Connecteurs.h"
#include "../include/ParseError.h"

namespace LogiqueParser
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

    FormuleTseitinSimple parse(std::string& fileName);
    FormuleTseitinSimple parse(std::istream& inputStream);

    void setResult(FormuleTseitinSimple& result);
private:
    Lexer* lexer;
    Parser* parser;
    FormuleTseitinSimple result;

    friend class Parser;
    friend class Lexer;
};

}

#endif // DRIVER_H
