#ifndef LANCEURSOLVEUR_H
#define LANCEURSOLVEUR_H

#include "Solveur.h"
#include "TheorieGreffon.h"
#include "ArgumentsParser.h"

enum HeuristiqueType {
    SIMPLE,
    RAND,
    MALIN,
    MOMS,
    DLIS,
    DLISVARIANTE
};

enum SolveurType {
    DPLL,
    WATCHED_LITERALS,
    DAVIS_PUTNAM,
    MINISAT
};

class LanceurSolveur
{
public:
    LanceurSolveur(ArgumentsParser& arguments_, std::string debutCommentaire, SolveurType solveurParDefaut = DPLL, HeuristiqueType heuristiqueParDefaut = SIMPLE );
    ~LanceurSolveur();
    Formule execute(Formule& formule, TheorieGreffon& theorieGreffon);
    std::streambuf* getBufferSortie() __attribute__((pure));
    static std::vector<std::string> getNomsOptions();

private:
    SolveurType getSolveur();
    HeuristiqueType getHeuristique();
    ArgumentsParser arguments;
    std::string debutCommentaire;
    SolveurType solveurParDefaut;
    HeuristiqueType heuristiqueParDefaut;
};

#endif // LANCEURSOLVEUR_H
