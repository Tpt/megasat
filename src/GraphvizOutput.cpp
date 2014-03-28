#include "../include/GraphvizOutput.h"
#include<sstream>

using namespace std;

GraphvizOutput::GraphvizOutput(Graphe& graphe_, Formule& formule_, map<string, int> correspondances_, int k_) :
graphe(graphe_), formule(formule_), correspondances(correspondances_), k(k_), tailleCodeCouleurSommet(ceil(log2(k_)))
{}

void GraphvizOutput::affiche(std::streambuf* sortie)
{
    ostream out(sortie);
    out << "digraph G {\n";

    for(Arete arete : graphe.getAretes())
        out << arete.getExtremiteGauche() + 1 << " -- " << arete.getExtremiteDroite() + 1 << ";\n";

    for(int sommet = 0; sommet < graphe.getSommetNumber(); sommet++)
    {
        out << sommet + 1 << " [color=" << getCouleur(sommet) << "];\n";
    }
    cout << "0-0 " << formule.getVar(correspondances["0-0"])->getVal() << "1-0 " << formule.getVar(correspondances["1-0"])->getVal() << endl;
    out << "}\n";
}

int GraphvizOutput::getCouleur(int sommet)
{
    int couleur = 0;
    for(int bit = 0; bit < tailleCodeCouleurSommet; bit++)
    {
        couleur *= 2;
        ostringstream os;
        os << sommet << '-' << bit;
        if(formule.getVar(correspondances[os.str()])->getVal())
            couleur += 1;
    }
    return couleur;
}