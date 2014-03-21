#ifndef GrapheParser_H
#define GrapheParser_H

#include<iostream>
#include"Graphe.h"
#include"ParseError.h"

class ColParser
{
public:
    Graphe parse(std::string &fileName);
    Graphe parse(std::istream &istream);

private:
    std::string getNextLine(std::istream &inputStream);
};

#endif
