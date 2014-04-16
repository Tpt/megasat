#ifndef LATEXPRINTER
#define LATEXPRINTER

#include "Preuve.h"
#include<string>
#include<map>

#define PREUVE 0
#define CLAUSE 1

#define TAILLE_MAX 20

class LatexPrinter //Prononcé LatechhhPrintère
{
public:
    LatexPrinter(Preuve preuve);
    ~LatexPrinter();
    std::string getCodeLatex() const {return latex;};
    void saveCodeLatex(std::string filename);

    static int genUid(unsigned int param);
    static std::map<unsigned int, int> nextUid;

private:
    void initCodeMinimal();
    void finaliseCodeMinimal();
    long unsigned int largeurDeLaPreuve(Preuve p) const;
    void genCodeLatex();
    std::string clauseToLatex(const std::vector<int>& clause) const;
    std::string litToLatex(int literal) const;
    std::string toString(int v) const;
    std::string preuveToLatex(Preuve p, int pos) const;
    std::string preuveToLatex(Preuve p, long unsigned int numPreuve, long unsigned int preuveUtilisee, int pos) const;
    std::string decouperPreuveEtLatex(Preuve p) const;
    std::vector<std::pair<Preuve,int>> decouperPreuve(Preuve p) const;

    std::string clauseToLatex(const std::vector<int>& clause, int gras) const;
    std::string litToLatex(int literal, int gras) const;


    Preuve preuve;
    std::string latex;
    std::vector<int> literauxResolus;
};

#endif // LATEXPRINTER
