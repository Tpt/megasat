#include<iostream>
#include"include/TransformationTseitin.h"
#include"include/LanceurSolveur.h"
#include"include/FormuleTseitin.h"
#include"parser/egalite/driver.h"
#include"include/InsatisfiableException.h"
#include"include/TheorieGreffonEgalite.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

FormuleTseitin<AtomeEgalite> parseFormuleFile(string fileName);

FormuleTseitin<AtomeEgalite> parseFormuleFile(string fileName)
{
    EgaliteParser::Driver parserDriver;
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

int main(int argc, char *argv[])
{
    vector<string> nomArguments(1);
    nomArguments[0]="inputFile";
    ArgumentsParser arguments(nomArguments, LanceurSolveur::getNomsOptions(), 1);
    arguments.parse(argc, argv);

    if(arguments.demandeAide())
    {
        cout<<endl<<"Syntaxe :"<<endl;
        cout<<"./egalite_solver nom_de_fichier.txt"<<endl;

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

    FormuleTseitin<AtomeEgalite>* formuleTseitin = new FormuleTseitin<AtomeEgalite>(parseFormuleFile(arguments.getArgument("inputFile")));

    TransformationTseitin<AtomeEgalite> normalisateur(formuleTseitin);

    auto beginTime = system_clock::now();
    Formule formule(normalisateur.normaliser());
    formuleTseitin->free();
    delete formuleTseitin;

    try
    {
        TheorieGreffonEgalite theorieGreffon;
        vector<AtomeEgalite> correspondance(normalisateur.getCorrespondance().size());
        for(pair<AtomeEgalite, int> t : normalisateur.getCorrespondance())
            correspondance[static_cast<size_t>(t.second - 1)]=t.first;

        theorieGreffon.setCorrespondanceAtomes(correspondance);

        formule = lanceur.execute(formule, theorieGreffon);

        out << "s SATISFIABLE" << endl;

        pair<vector<AtomeEgalite>,vector<AtomeEgalite>> etat = theorieGreffon.getEtatCourant();
        for(AtomeEgalite atome : etat.first)
            out << "x" << atome.getI() << " = x" << atome.getJ() << endl;
        for(AtomeEgalite atome : etat.second)
            out << "x" << atome.getI() << " != x" << atome.getJ() << endl;
    }
    catch(InsatisfiableException)
    {
        out << "s UNSATISFIABLE" << endl;
    }
    out << "c Resolu en : " << duration_cast<duration<double>>(system_clock::now() - beginTime).count() << " secondes" << endl;


    return EXIT_SUCCESS;
}
