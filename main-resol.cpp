#include"include/LanceurSolveur.h"
#include"include/Formule.h"
#include"include/CnfParser.h"
#include"include/InsatisfiableException.h"
#include"include/ErreurResolutionException.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

Formule parseCnfFile(string fileName);

Formule parseCnfFile(string fileName)
{
    CnfParser cnfParser;

    try
    {
        return cnfParser.parse(fileName);
    }
    catch(ParseError& e)
    {
        cerr << "c Erreur du parser : " << e.getMessage() << "\nc Arrêt de la résolution." << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    vector<string> nomArguments(1);
    nomArguments[0] = "inputFile";
    ArgumentsParser arguments(nomArguments, LanceurSolveur::getNomsOptions(), 1);
    arguments.parse(argc, argv);

    if(arguments.demandeAide())
    {
        cout<<endl<<"Syntaxe :"<<endl;
        cout<<"./resol nom_de_fichier.cnf"<<endl;
        cout<<"Où nom_de_fichier.cnf est au format CNF"<<endl;

        cout<<endl<<"Solveurs : "<<endl;
        cout<<"-dp              Davis-Putnam"<<endl;
        cout<<"-dpll            DPLL (défaut)"<<endl;
        cout<<"-wl              Watched Literals"<<endl;
        cout<<"-rapide          Un solveur plus rapide encore"<<endl<<endl;
        cout<<"Heuristiques (seulement avec -dpll et -wl) : "<<endl;
        cout<<"-simple          (default)"<<endl;
        cout<<"-rand"<<endl;
        cout<<"-malin"<<endl;
        cout<<"-dlis"<<endl;
        cout<<"-moms"<<endl<<endl;
        cout<<"Clause Learning (seulement avec -dpll et -wl) :"<<endl;
        cout<<"-cl              Clause Learning simple"<<endl;
        cout<<"-cl-interac      Clause Learning interactif"<<endl<<endl;
        cout<<"Divers :"<<endl;
        cout<<"-v               Verbose"<<endl;
        cout<<"-s               Silencieux"<<endl;
        cout<<"-c               Vérifie la solution à la fin de la résolution"<<endl;
        cout<<"-h               Vous y êtes"<<endl;
        cout<<"--help           Vous y êtes"<<endl<<endl;
        return(EXIT_SUCCESS);
    }

    LanceurSolveur lanceur(arguments, "c");

    Formule formule = parseCnfFile(arguments.getArgument("inputFile"));
    ostream out(lanceur.getBufferSortie());

    auto beginTime = system_clock::now();
    try
    {
        TheorieGreffonLogique theorieGreffon;
        formule = lanceur.execute(formule, theorieGreffon);

        out << "s SATISFIABLE" << endl;
        for(int i = 1; i <= formule.getNombreDeVariables(); i++)
        {
            if(formule.getVar(i)->getVal())
                out << "v " << i << endl;
            else
                out << "v " << -i << endl;
        }
    }
    catch(InsatisfiableException)
    {
        out << "s UNSATISFIABLE" << endl;
    }
    catch(ErreurResolutionException)
    {
        out << "s SATISFIABLE" << endl;
        for(int i = 1; i <= formule.getNombreDeVariables(); i++)
        {
            if(formule.getVar(i)->getVal())
                out << "v " << i << endl;
            else
                out << "v " << -i << endl;
        }
        cerr << "Erreur lors de la résultion" << endl;
    }
    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;

    return EXIT_SUCCESS;
}
