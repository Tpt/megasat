#include "../include/MinisatSolveur.h"
#include<cstdlib>

using namespace std;

MinisatSolveur::MinisatSolveur(Formule& formule_) : Solveur(formule_)
{}

bool MinisatSolveur::isSatifiable()
{
    filebuf fb;
    if(fb.open(".temp-in.cnf", ios::out) == nullptr)
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

    system("minisat .temp-in.cnf .temp-out.cnf >/dev/null");
    remove(".temp-in.cnf");

    if(fb.open(".temp-out.cnf", ios::in) == nullptr)
        exit(EXIT_FAILURE);
    istream outFileStream(&fb);

    string state;
    outFileStream >> state;
    if(state == "UNSAT")
    {
        fb.close();
        remove(".temp-out.cnf");
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