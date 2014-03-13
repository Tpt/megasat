#include <fstream>
#include <istream>

#include "driver.h"
#include "lexer.h"

using namespace std;

namespace LogiqueParser {

Driver::Driver()
: lexer(new Lexer()),
  parser(new Parser(*this)) {}

Driver::~Driver() {
    delete parser;
    delete lexer;
}

void Driver::parse(const char* fileName) {
    filebuf fb;
    fb.open(fileName, std::ios::in);
    istream is(&fb);
    lexer->switch_streams(&is, &cerr);

    if (parser->parse() != 0) {
        // Error
        // Do something?
        return;
    }
}

}
