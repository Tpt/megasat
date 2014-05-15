#include<iostream>
#include"include/TransformationTseitin.h"
#include"include/LanceurSolveur.h"
#include"include/FormuleTseitin.h"
#include"parser/congruence/driver.h"
#include"include/InsatisfiableException.h"
#include"include/TheorieGreffonCongruence.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

FormuleTseitin<AtomeCongruence> parseFormuleFile(string fileName);

FormuleTseitin<AtomeCongruence> parseFormuleFile(string fileName)
{
    CongruenceParser::Driver parserDriver;
    try
    {
        return parserDriver.parse(fileName);
    }
    catch(ParseError& e)
    {
        cerr << "c Erreur du parser : " << e.getMessage() << "\nc Arrêt de la résolution." << endl;
        exit(EXIT_FAILURE);
    }
}
string toString(FormuleTseitin<AtomeCongruence> t);
string toString(FormuleTseitin<AtomeCongruence> t)
{
    switch(t.getType())
    {
        case FormuleTseitin<AtomeCongruence>::VARIABLE :
            return t.getName().toString();
        case FormuleTseitin<AtomeCongruence>::NON :
            return "~" + toString(t.getOperandeG());
        case FormuleTseitin<AtomeCongruence>::OU :
            return "(" + toString(t.getOperandeG()) + " \\/ " + toString(t.getOperandeD()) + ")";
        case FormuleTseitin<AtomeCongruence>::ET :
            return "(" + toString(t.getOperandeG()) + " /\\ " + toString(t.getOperandeD()) + ")";
        case FormuleTseitin<AtomeCongruence>::IMPLIQUE :
            return "(" + toString(t.getOperandeG()) + " => " + toString(t.getOperandeD()) + ")";
        case FormuleTseitin<AtomeCongruence>::XOR :
            return "(" + toString(t.getOperandeG()) + " xor " + toString(t.getOperandeD()) + ")";
        default :
            return "P'tet ben, j'en sais rien...";
    }
}


int main(int argc, char *argv[])
{
    vector<string> nomArguments(1);
    nomArguments[0]="inputFile";
    ArgumentsParser arguments(nomArguments, LanceurSolveur::getNomsOptions(), 1);
    arguments.parse(argc, argv);

    if(arguments.demandeAide())
    {
        cout<<endl<<"Syntaxe :"<<endl;
        cout<<"./congruence_solver nom_de_fichier.txt"<<endl;

        cout<<endl<<"Solveurs : "<<endl;
        cout<<"-dp              Davis-Putnam"<<endl;
        cout<<"-dpll            DPLL (défaut)"<<endl;
        cout<<"-wl              Watched Literals"<<endl;
        cout<<"-rapide          Un solveur plus rapide encore"<<endl<<endl;
        cout<<"Heuristiques (seulement avec -dpll et -wl) : "<<endl;
        cout<<"-simple"<<endl;
        cout<<"-rand"<<endl;
        cout<<"-malin"<<endl;
        cout<<"-dlis"<<endl;
        cout<<"-moms            (default)"<<endl<<endl;
        cout<<"Clause Learning (seulement avec -dpll et -wl) :"<<endl;
        cout<<"-cl              Clause Learning simple"<<endl;
        cout<<"-cl-interac      Clause Learning interactif"<<endl<<endl;
        cout<<"Divers :"<<endl;
        cout<<"-v               Verbose"<<endl;
        cout<<"-s               Silencieux"<<endl;
        cout<<"-h               Vous y êtes"<<endl;
        cout<<"--help           Vous y êtes"<<endl<<endl;
        return(EXIT_SUCCESS);
    }


    LanceurSolveur lanceur(arguments, "c", SolveurType::DPLL, HeuristiqueType::MOMS);
    ostream out(lanceur.getBufferSortie());

    FormuleTseitin<AtomeCongruence>* formuleTseitin = new FormuleTseitin<AtomeCongruence>(parseFormuleFile(arguments.getArgument("inputFile")));

    cout<<toString(*formuleTseitin)<<endl;

    TransformationTseitin<AtomeCongruence> normalisateur(formuleTseitin);

    auto beginTime = system_clock::now();
    Formule formule(normalisateur.normaliser());
    formuleTseitin->free();
    delete formuleTseitin;

    try
    {
        TheorieGreffonCongruence theorieGreffon;
        vector<AtomeCongruence> correspondance(normalisateur.getCorrespondance().size());
        for(pair<AtomeCongruence, int> t : normalisateur.getCorrespondance())
            correspondance[static_cast<size_t>(t.second-1)]=t.first;

        theorieGreffon.setCorrespondanceAtomes(correspondance);

        formule = lanceur.execute(formule, theorieGreffon);

        vector<map<int, Terme>> unificateur(theorieGreffon.getSubstitutions());

        out << "s SATISFIABLE" << endl;

        for(map<int, Terme> t : unificateur)
        {
            for(pair<int, Terme> s : t)
            {
                out <<"x"<<s.first<<" -> "<<s.second.toString()<<endl;
            }
        }
    }
    catch(InsatisfiableException)
    {
        out << "s UNSATISFIABLE" << endl;
    }
    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;


    return EXIT_SUCCESS;
}
