#ifndef LANCEURSOLVEUR_H
#define LANCEURSOLVEUR_H

#include "Solveur.h"
#include "ArgumentsParser.h"

enum Heuristique {
    SIMPLE,
    RAND,
    MALIN,
    MOMS,
    DLIS
};

class LanceurSolveur
{
public:
    LanceurSolveur(ArgumentsParser& arguments_, std::string debutCommentaire, Heuristique heuristiqueParDefaut = SIMPLE);
    ~LanceurSolveur();
    Formule execute(Formule& formule);
    std::streambuf* getBufferSortie();
    static std::vector<std::string> getNomsOptions();

private:
    Heuristique getHeuristique();
    ArgumentsParser arguments;
    std::string debutCommentaire;
    Heuristique heuristiqueParDefaut;
};

#endif // LANCEURSOLVEUR_H
