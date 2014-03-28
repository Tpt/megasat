#include <sstream>
#include <fstream>
#include <string>
#include "../include/ColParser.h"

using namespace std;

Graphe ColParser::parse(string &fileName)
{
    filebuf fb;
    if(fb.open(fileName, ios::in) == nullptr)
    {
        throw ParseError("Le fichier d'entrée n'existe pas !");
    }
    istream fileStream(&fb);
    
    return parse(fileStream);
}

Graphe ColParser::parse(istream &istream)
{
    istringstream headerStream(getNextLine(istream));
    string header1;
    string header2;
    int nodeNumber;
    int edgeNumber;
    if(!(headerStream >> header1 >> header2 >> nodeNumber >> edgeNumber && header1 == "p" && header2 == "edge"))
    {
        throw ParseError("L'entête du fichier est invalide !");
    }

    Graphe graphe(nodeNumber);
    for(int i = 0; i < edgeNumber; i++)
    {
        string line = getNextLine(istream);
        istringstream lineStream(line);

        char type;
        int v, w;
        lineStream >> type >> v >> w;
        graphe.addArete(Arete(v - 1, w - 1));
    }

    return graphe;
}

string ColParser::getNextLine(istream &inputStream)
{
    string str;
    while(true)
    {
        getline(inputStream, str);
        if(!str.empty() && (str[0] == 'e' || str[0] == 'p')) //on ne prend que l'entête et les arêtes
            return str;
    }
}