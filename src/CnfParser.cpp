#include <sstream>
#include <string>
#include "../include/CnfParser.h"

using namespace std;

Formule CnfParser::parse(string &fileName)
{
    filebuf fb;
    if(fb.open(fileName, ios::in) == nullptr)
    {
        throw ParseError("Le fichier d'entrée n'existe pas !");
    }
    istream fileStream(&fb);

    return parse(fileStream);
}

Formule CnfParser::parse(istream &istream)
{
    istringstream headerStream(getNextLine(istream));
    string header1;
    string header2;
    int variableNumber;
    int clauseNumber;
    if(!(headerStream >> header1 >> header2 >> variableNumber >> clauseNumber && header1 == "p" && header2 == "cnf"))
    {
        throw ParseError("L'entête du fichier est invalide !");
    }

    Formule formula(variableNumber);
    for(int i = 0; i < clauseNumber; i++)
    {
        istringstream clauseStream(getNextLine(istream));

        Clause* clause = new Clause(variableNumber);
        int value = 1;
        while(clauseStream >> value && value != 0)
            clause->addLiteral(formula.getLiteral(value));
        formula.addClause(clause);
    }
    return formula;
}

string CnfParser::getNextLine(istream &inputStream)
{
    while(true)
    {
        string str;
        getline(inputStream, str);
        if(str.empty())
            throw ParseError("Il manque des lignes dans le fichier !");
        else if(str[0] != 'c') //on n'a pas affaire à un commentaire
            return str;
    }
}