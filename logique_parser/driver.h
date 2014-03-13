#ifndef DRIVER_H
#define DRIVER_H

namespace LogiqueParser {

    class Parser;
    class Lexer;

    class Driver {
    public:
        Driver();
        ~Driver();

        void parse(const char* fileName);

    private:
        Lexer* lexer;
        Parser* parser;

        friend class Parser;
        friend class Lexer;
    };

}

#endif // DRIVER_H
