#include "../include/LatexPrinter.h"
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

map<unsigned int, int> LatexPrinter::nextUid = map<unsigned int, int>();

LatexPrinter::LatexPrinter(Preuve preuve_) :
preuve(preuve_), latex(""), literauxResolus(preuve_.getLiterauxResolus())
{
    cout<<"Vous qui arrivez dans cette fonction, abandonnez toute espérance !"<<endl;
    preuve.print();
    genCodeLatex();
    literauxResolus.push_back(0);
}

LatexPrinter::~LatexPrinter()
{}

void LatexPrinter::saveCodeLatex(string filename)
{
    ofstream file(filename);
    file<<latex;
    file.close();
}

long unsigned int LatexPrinter::largeurDeLaPreuve(Preuve p) const
{
    long unsigned int total=0;
    for(vector<int> e : p.getPremisses())
        total+=e.size()+2;

    return total;
}

void LatexPrinter::genCodeLatex()
{
    initCodeMinimal();

    latex+=decouperPreuveEtLatex(preuve);

    finaliseCodeMinimal();
}

void LatexPrinter::initCodeMinimal()
{
    latex+="\\documentclass{article}\n"
           "\\usepackage{mathpartir}\n"
           "\\usepackage[utf8]{inputenc}\n"
           "\\usepackage[francais]{babel}\n"
           "\\newcommand{\\non}[1]{\\overline{#1}}\n"
           "\\newcommand{\\varv}[1]{x_{#1}}\n"
           "\\newcommand{\\varf}[1]{\\non{\\varv{#1}}}\n"
           "\\newcommand{\\cl}[1]{\\mathtt{C_{#1}}:~}\n"
           "\\newcommand{\\preuve}[1]{\\mathtt{\\Pi_{#1}}}\n"
           "\\title{Une preuve !}\n"
           "\\author{Marc \\textsc{Chevalier}\\\\ Thomas \\textsc{Pellissier Tanon}}"
           "\\begin{document}\n"
           "\\maketitle\n"
           "Preuve de résolution pour la clause :\n"
           "$$"+clauseToLatex(preuve.getConclusion())+"\\enspace .$$ \n\n";
}

string LatexPrinter::decouperPreuveEtLatex(Preuve p) const
{
    vector<pair<Preuve,int>> t(decouperPreuve(p));
    string sortie="";
    unsigned int pos=0;

    for(unsigned int i=0; i < t.size(); ++i)
    {
        sortie+=preuveToLatex(t[i].first, t.size()-static_cast<unsigned int>(t[i].second), (t.size()-static_cast<unsigned int>(t[i].second)+1)%t.size(), pos);
        pos+=static_cast<unsigned int>(t[i].first.getPremisses().size());
    }

    return sortie;
}

vector<pair<Preuve,int>> LatexPrinter::decouperPreuve(Preuve p) const
{
    vector<pair<Preuve, int>> sortie; ///Numéro de la preuve. 0 pour la racine de la preuve.
    vector<vector<int>> premisses=p.getPremisses();
    vector<vector<int>> conclusions=p.getConclusions();
    vector<vector<int>> conclusions_temp;
    vector<vector<int>> premisses_temp;
    long unsigned int taille_temp=0;

    for(unsigned int i=0; i<premisses.size(); ++i)
    {
        premisses_temp.push_back(premisses[i]);
        conclusions_temp.push_back(conclusions[i]);
        taille_temp+=premisses[static_cast<size_t>(i)].size()+2;
        if(taille_temp+conclusions[i+1].size()>TAILLE_MAX)
        {
            conclusions_temp.push_back(conclusions[i+1]);
            sortie.push_back(pair<Preuve,int>(Preuve(conclusions_temp,premisses_temp),genUid(PREUVE)));
            conclusions_temp.clear();
            premisses_temp.clear();
            taille_temp=0;
        }
    }

    if(taille_temp>0)
    {
        conclusions_temp.push_back(conclusions[premisses.size()]);
        sortie.push_back(pair<Preuve,int>(Preuve(conclusions_temp,premisses_temp),genUid(PREUVE)));
        conclusions_temp.clear();
        premisses_temp.clear();
        taille_temp=0;
    }

    return sortie;
}

string LatexPrinter::preuveToLatex(Preuve p, long unsigned int numPreuve, long unsigned int preuveUtilisee, unsigned int pos) const
{
    vector<vector<int>> premisses=p.getPremisses();
    vector<vector<int>> conclusions=p.getConclusions();
    string sortie="";
    sortie+="\\begin{mathpar} \n ";
    if(numPreuve!=0)
        sortie+="\\preuve{"+toString(static_cast<int>(numPreuve))+"}:~ \n ";

    for(unsigned int i=0; i<premisses.size(); ++i)
    {
        sortie+="\\inferrule{ \n ";
    }

    if(preuveUtilisee==0)
        sortie+=clauseToLatex(conclusions[0],literauxResolus[pos+0]);
    else
        sortie+="\\preuve{ "+toString(static_cast<int>(preuveUtilisee))+" } \n ";

    for(unsigned int i=0; i<premisses.size(); ++i)
    {
        sortie+="  \\and \n ";
        sortie+=clauseToLatex(premisses[i],literauxResolus[pos+i]);
        sortie+=" \n } { \n ";
        sortie+=clauseToLatex(conclusions[i+1],literauxResolus[pos+i+1]);
        sortie+=" } \n ";
    }
    sortie+="\\end{mathpar}\\ \n \n \n";
    return sortie;
}

string LatexPrinter::preuveToLatex(Preuve p, unsigned int pos) const
{

    vector<vector<int>> premisses=p.getPremisses();
    vector<vector<int>> conclusions=p.getConclusions();
    string sortie="\\begin{mathpar}";

    for(unsigned int i=0; i<premisses.size(); ++i)
    {
        sortie+="\\inferrule{ ";
    }

    sortie+=clauseToLatex(conclusions[0],literauxResolus[pos+0]);

    for(unsigned int i=0; i<premisses.size(); ++i)
    {
        sortie+=" \and ";
        sortie+=clauseToLatex(premisses[i],literauxResolus[pos+i]);
        sortie+=" } { ";
        sortie+=clauseToLatex(conclusions[i+1],literauxResolus[pos+i+1]);
        sortie+=" } ";
    }
    sortie+="\\end{mathpar}";
    return sortie;
}

string LatexPrinter::clauseToLatex(const vector<int>& clause, int gras) const
{
    string sortie=litToLatex(clause[0], gras);

    for(unsigned int i=1; i<clause.size(); ++i)
        sortie+=" \\lor "+litToLatex(clause[i],gras);

    return sortie;
}

string LatexPrinter::litToLatex(int literal, int gras) const
{
    if(gras==literal || gras== -literal)
    {
        if(literal>0)
            return "\\mathbf{\\varv{"+toString(literal)+"}}";
        return "\\mathbf{\\varf{"+toString(-literal)+"}}";
    }

    if(literal>0)
        return "\\varv{"+toString(literal)+"}";
    return "\\varf{"+toString(-literal)+"}";
}

string LatexPrinter::clauseToLatex(const vector<int>& clause) const
{
    string sortie=litToLatex(clause[0]);

    for(unsigned int i=1; i<clause.size(); ++i)
        sortie+=" \\lor "+litToLatex(clause[i]);

    return sortie;
}

string LatexPrinter::litToLatex(int literal) const
{
    if(literal>0)
        return "\\varv{"+toString(literal)+"}";
    return "\\varf{"+toString(-literal)+"}";
}

string LatexPrinter::toString(int v) const
{
    stringstream ss;
    ss<<v;
    return ss.str();
}

void LatexPrinter::finaliseCodeMinimal()
{
    latex+="\\end{document}\n";
}

int LatexPrinter::genUid(unsigned int param)
{
    ++LatexPrinter::nextUid[param];
    return LatexPrinter::nextUid[param];
}

