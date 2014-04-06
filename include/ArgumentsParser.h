#ifndef ARGUMENTSPARSER_H
#define ARGUMENTSPARSER_H

#include<string>
#include<vector>
#include<map>

class ArgumentsParser
{
public:
    ArgumentsParser(std::vector<std::string> nomsArguments, std::vector<std::string> nomsOptions, int nombreArgumentsObligatoires);
    void parse(int argc, char* argv[]);
    std::string getArgument(std::string nom);
    bool getOption(std::string nom);
private:
    std::map<std::string, std::string> arguments;
    std::vector<std::string> nomsArguments;
    std::map<std::string, bool> options;
    int nombreArgumentsObligatoires;
};

#endif
