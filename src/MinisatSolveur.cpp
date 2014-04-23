#include "../include/MinisatSolveur.h"
#include<cstdlib>
#include<unistd.h>

using namespace std;

MinisatSolveur::MinisatSolveur(Formule& formule_) : Solveur(formule_)
{}

inline string toString(const int i);
inline string toString(const int i) {
    stringstream s;
    s << i;
    return s.str();
}

bool MinisatSolveur::isSatifiable()
{
    int uid = getpid();
    string inputFile = ".temp-in-" + toString(uid) + ".cnf";
    string outputFile = ".temp-out-" + toString(uid) + ".cnf";
    filebuf fb;
    if(fb.open(inputFile, ios::out) == nullptr)
        exit(EXIT_FAILURE);
    ostream inFileStream(&fb);

    auto clauses = formule.getClauses();
    inFileStream << "p cnf " << formule.getNombreDeVariables() << ' ' << clauses.size() << endl;
    for(auto clause : clauses)
    {
        for(auto literal : clause->getLiteraux())
        {
            inFileStream << literal->getId() << ' ';
        }
        inFileStream << '0' << endl;
    }
    fb.close();

    system(("minisat " + inputFile + ' ' + outputFile + " >/dev/null").c_str());
    remove(inputFile.c_str());

    if(fb.open(outputFile, ios::in) == nullptr)
        exit(EXIT_FAILURE);
    istream outFileStream(&fb);

    string state;
    outFileStream >> state;
    if(state == "UNSAT")
    {
        fb.close();
        remove(outputFile.c_str());
        return false;
    }
    else if(state == "SAT")
    {
        int i;
        while(outFileStream >> i && i != 0) {
            formule.setVar(abs(i), i > 0);
        }
        fb.close();
        remove(".temp-out.cnf");
        return true;
    }

    fb.close();
    remove(".temp-out.cnf");
    exit(EXIT_FAILURE);
}