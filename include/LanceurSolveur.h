#ifndef LANCEURSOLVEUR_H
#define LANCEURSOLVEUR_H

#include "Solveur.h"
#include<cstring>
#include<string>

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
        LanceurSolveur();
        ~LanceurSolveur();
        std::string getFileName() const;
        void parseOptions(int argc, char* argv[]);
        void ExecuteEtAfficheResultat(Formule& formule);
        bool isVerbose() const;

    private:
        std::string fileName;
        bool verbose;
        bool avecLiterauxSurveilles;
        bool utiliserDavisPutnam;
        Heuristique typeHeuristique;
};

#endif // LANCEURSOLVEUR_H
