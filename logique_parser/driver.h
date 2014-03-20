#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include "../include/FormuleTseitin.h"
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

    FormuleTseitin parse(std::string& fileName);
    FormuleTseitin parse(std::istream& inputStream);

    void setResult(FormuleTseitin& result);
private:
    Lexer* lexer;
    Parser* parser;
    FormuleTseitin result;

    friend class Parser;
    friend class Lexer;
};

}

#endif // DRIVER_H
