#include <sstream>
#include <string>
#include "CnfParser.h"

std::string getNextLine(std::istream &inputStream)
{
	while(true)
    {
		std::string str;
		std::getline(inputStream, str);
		if(str == "")
			throw ParseError();
        else if(str[0] != 'c') //on n'a pas affaire à un commentaire
			return str;
	}
}

Formule CnfParser::parse(std::string &fileName)
{
	std::filebuf fb;
    fb.open(fileName, std::ios::in);
    std::istream fileStream(&fb);

	return parse(fileStream);
}

Formule CnfParser::parse(std::istream &istream)
{
	std::istringstream headerStream(getNextLine(istream));
	std::string header1;
	std::string header2;
	int variableNumber;
	int clauseNumber;
	if(!(headerStream >> header1 >> header2 >> variableNumber >> clauseNumber && header1 == "p" && header2 == "cnf"))
    {
		throw ParseError();
	}
    
	Formule formula(variableNumber);
	for(int i = 0; i < clauseNumber; i++) {
		std::istringstream clauseStream(getNextLine(istream));
        
        Clause* clause = new Clause(variableNumber);
        int value = 1;
        while(clauseStream >> value && value != 0)
            clause->addLiteral(formula.getLiteral(value));
        formula.addClause(clause);
	}
    
	return formula;
}