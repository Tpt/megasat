#ifndef LANCEURSOLVEUR_H
#define LANCEURSOLVEUR_H

#include "Solveur.h"
#include "ArgumentsParser.h"

enum HeuristiqueType {
    SIMPLE,
    RAND,
    MALIN,
    MOMS,
    DLIS
};

enum SolveurType {
    DPLL,
    WATCHED_LITERALS,
    DAVIS_PUTNAM,
    MINISAT
};

enum TheorieType {
    LITERALS
};

class LanceurSolveur
{
public:
    LanceurSolveur(ArgumentsParser& arguments_, std::string debutCommentaire, SolveurType solveurParDefaut = DPLL, HeuristiqueType heuristiqueParDefaut = SIMPLE, TheorieType theorieType = LITERALS);
    ~LanceurSolveur();
    Formule execute(Formule& formule);
    std::streambuf* getBufferSortie() __attribute__((pure));
    static std::vector<std::string> getNomsOptions();

private:
    SolveurType getSolveur();
    HeuristiqueType getHeuristique();
    ArgumentsParser arguments;
    std::string debutCommentaire;
    SolveurType solveurParDefaut;
    HeuristiqueType heuristiqueParDefaut;
    TheorieType theorieType;
};

#endif // LANCEURSOLVEUR_H
