#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include "../include/Connecteurs.h"

namespace LogiqueParser {

    class Parser;
    class Lexer;

    class Driver {
    public:
        Driver();
        ~Driver();

        FormuleTseitinSimple parse(const char* fileName);
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
