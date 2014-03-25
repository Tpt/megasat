#ifndef LANCEURSOLVEUR_H
#define LANCEURSOLVEUR_H

#include "Solveur.h"
#include<cstring>
#include<string>
#include<map>

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
        Formule execute(Formule& formule);
        bool isVerbose() const;
        std::streambuf* getBufferSortie() const;

    private:
        std::string fileName;
        std::string fileSortieName;
        bool existeFichierSortie;
        bool verbose;
        bool avecLiterauxSurveilles;
        bool utiliserDavisPutnam;
        Heuristique typeHeuristique;
};

#endif // LANCEURSOLVEUR_H
