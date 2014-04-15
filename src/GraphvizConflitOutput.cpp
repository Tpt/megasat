#include "../include/GraphvizConflitOutput.h"
#include<sstream>
#include<map>

using namespace std;

GraphvizConflitOutput::GraphvizConflitOutput(std::vector<std::pair<int,std::vector<int>>>& pile_) : pile(pile_)
{}

void GraphvizConflitOutput::affiche(std::streambuf* sortie)
{
    ostream out(sortie);
    out << "digraph G {\n";

    map<int, pair<int, string>> sommets; //id => label + color

    //les déductions
    for(int i = 0; i < pile.size() - 1; i++)
    {
        auto deduction = pile[i];
        int sommet = abs(deduction.first);
        sommets[sommet] = pair<int, string>(deduction.first, "blue");
        for( auto literalPere : deduction.second)
        {
            int pere = abs(literalPere);
            if(pere != sommet)
                out << pere << " -> " << sommet << ";\n";
        }
    }

    //on colore le sommet de départ en vert
    sommets[abs(pile[0].first)].second = "green";

    //le conflit
    auto deduction = pile[pile.size() - 1];
    int sommet = abs(deduction.first);
    sommets[-sommet] = pair<int, string>(deduction.first, "red");
    sommets[sommet].second = "red";
    for( auto literalPere : deduction.second)
    {
        int pere = abs(literalPere);
        if(pere != sommet)
            out << pere << " -> " << -sommet << ";\n";
    }

    for(auto sommet : sommets)
        out << sommet.first << " [color=\"" << sommet.second.second << "\",style=filled,label=\"" << sommet.second.first << "\"];\n";

    out << "}\n";
}