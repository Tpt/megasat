#ifndef LANCEURSOLVEUR_H
#define LANCEURSOLVEUR_H

#include "Solveur.h"
#include "ArgumentsParser.h"

class LanceurSolveur
{
public:
    LanceurSolveur(ArgumentsParser& arguments_, std::string debutCommentaire);
    ~LanceurSolveur();
    Formule execute(Formule& formule);
    std::streambuf* getBufferSortie();
    static std::vector<std::string> getNomsOptions();

private:
    ArgumentsParser arguments;
    std::string debutCommentaire;
};

#endif // LANCEURSOLVEUR_H
