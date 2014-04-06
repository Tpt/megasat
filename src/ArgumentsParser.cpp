#include<iostream>
#include "../include/ArgumentsParser.h"

using namespace std;

ArgumentsParser::ArgumentsParser(vector<string> nomsArguments_, vector<string> nomsOptions, int nombreArgumentsObligatoires_) :
arguments(map<string,string>()), nomsArguments(nomsArguments_), options(map<string,bool>()), nombreArgumentsObligatoires(nombreArgumentsObligatoires_)
{
    for(string option : nomsOptions)
        options[option] = false;
}

void ArgumentsParser::parse(int argc, char* argv[])
{
    int compteurArguments = 0;
    for(int i = 1; i < argc; i++)
    {
        if( argv[i][0] == '-' )
        {
            string option = string(argv[i]).substr(1);
            if(options.count(option) == 0)
                cerr << "c Option inconnue : " << argv[i] << endl;
            else
                options[option] = true;
        }
        else
        {
            if(compteurArguments >= static_cast<int>(nomsArguments.size()))
            {
                cerr << "c L'argument " << argv[i] << " est en trop" << endl;
            }
            else
            {
                arguments[nomsArguments[static_cast<size_t>(compteurArguments)]] = argv[i];
                compteurArguments++;
            }
        }
    }
    if(compteurArguments < nombreArgumentsObligatoires)
    {
        cerr << "c Seulement " << compteurArguments << " arguments ont été fournis." << endl;
        exit( EXIT_FAILURE );
    }
}

string ArgumentsParser::getArgument(string nom)
{
    return arguments[nom];
}

bool ArgumentsParser::getOption(string nom)
{
    return options[nom];
}
