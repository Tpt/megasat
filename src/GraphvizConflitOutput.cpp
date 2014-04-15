#include "../include/GraphvizConflitOutput.h"
#include<sstream>

using namespace std;

GraphvizConflitOutput::GraphvizConflitOutput(std::vector<std::pair<int,std::vector<int>>>& pile_) : pile(pile_)
{}

void GraphvizConflitOutput::affiche(std::streambuf* sortie)
{
    ostream out(sortie);
    out << "digraph G {\n";

    for(auto deduction : pile)
    {
        int sommet = abs(deduction.first);
        if(sommet == 0)
            continue;
        out << sommet << " [color=blue,style=filled,label=\"" << deduction.first << "\"];\n";
        for( auto literalPere : deduction.second)
        {
            int pere = abs(literalPere);
            if(pere != sommet)
                out << pere << " -> " << sommet << ";\n";
        }
    }

    out << "}\n";
}