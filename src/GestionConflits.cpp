#include "../include/GestionConflits.h"
#include "../include/GraphvizConflitOutput.h"
#include "../include/LatexPrinter.h"
#include<iostream>

using namespace std;

GestionConflits::GestionConflits(int prochainConflit_)
: conflitsNum(0), prochainConflit(prochainConflit_)
{}

GestionConflits::~GestionConflits()
{}

void GestionConflits::onBeggining(Formule* formule)
{}

void GestionConflits::onDeduction(Literal* literal, int clauseUid)
{}

void GestionConflits::onChoix(int literalId)
{}

pair<int,vector<int>> GestionConflits::onConflit(int clauseUid)
{
    conflitsNum++;
    return pair<int,vector<int>>(-1, vector<int>(0));
}

int GestionConflits::getConflitsNum() const
{
    return conflitsNum;
}


GestionConflitsApprentissage::GestionConflitsApprentissage(int prochainConflit_)
 : GestionConflits(prochainConflit_), clauses(vector<vector<int>>()), pileDeDeductions(vector<pair<int,vector<int>>>())
{}

void GestionConflitsApprentissage::onBeggining(Formule* formule)
{
    clauses = vector<vector<int>>();
    for(Clause* clause : formule->getClauses())
    {
        addClause(clause);
    }
}

void GestionConflitsApprentissage::onDeduction(Literal* literal, int clauseUid)
{
    pileDeDeductions.push_back(pair<int,vector<int>>(literal->getId(), clauses[clauseUid]));
}

void GestionConflitsApprentissage::onChoix(int literalId)
{
    pileDeDeductions = vector<pair<int,vector<int>>>();
    pileDeDeductions.push_back(pair<int,vector<int>>(literalId, vector<int>()));
}

pair<int,vector<int>> GestionConflitsApprentissage::onConflit(int clauseUid)
{
    GestionConflits::onConflit(clauseUid);
    pileDeDeductions.push_back(pair<int,vector<int>>(getLiteralConflictuel(clauseUid), clauses[clauseUid]));
    ConstructeurPreuve constructeurPreuve(pileDeDeductions);

    if(conflitsNum == prochainConflit)
        displayInterface(constructeurPreuve);

    int uid = Clause::genUid();
    vector<int> clauseAAjouter = constructeurPreuve.getNouvelleClause();
    addClause(clauseAAjouter, uid);
    return pair<int,vector<int>>(uid, clauseAAjouter);
}

int GestionConflitsApprentissage::getLiteralConflictuel(int clauseUid) const
{
    for(int literalId : clauses[clauseUid])
    {
        for(auto deduction : pileDeDeductions)
        {
            if(deduction.first == -literalId)
                return literalId;
        }
    }

    return 0;
}

void GestionConflitsApprentissage::displayInterface(ConstructeurPreuve constructeurPreuve)
{
    cout << conflitsNum << "° conflit !" << endl;

    char ch;
    while(cin >> ch)
    {
        switch(ch)
        {
            case 'g':
            {
                cout << "Fichier ?" << endl;
                string fileName;
                cin >> fileName;

                cout << "Sortie du graphe des conflits dans le fichier " << fileName << endl;
                GraphvizConflitOutput graphvizOut(pileDeDeductions);
                graphvizOut.affiche(fileName);
                break;
            }
            case 'r':
            {
                cout << "Fichier ?" << endl;
                string fileName;
                cin >> fileName;
                
                cout << "Sortie de la preuve dans le fichier " << fileName << endl;
                LatexPrinter latexPrinter(constructeurPreuve.getPreuve());
                latexPrinter.saveCodeLatex(fileName);
                break;
            }
            case 'c':
                cout << "Affichage lors du prochain conflit." << endl;
                prochainConflit++;
                return;
            case 's':
                int num;
                cin >> num;
                cout << "Affichage lors du " << num << " conflits plus loin." << endl;
                prochainConflit += num;
                return;
            case 't':
                cout << "Arrêt de l'affichage." << endl;
                return;
            default:
                cout << "Option inconnu : " << ch << endl;
        }
    }
}

void GestionConflitsApprentissage::addClause(const Clause* clause)
{
    vector<int> literaux;
    for(Literal* literal : clause->getLiteraux())
    {
        literaux.push_back(literal->getId());
    }

    addClause(literaux, clause->getUid());
}

void GestionConflitsApprentissage::addClause(vector<int> clause, int uid)
{
    if(uid >= static_cast<int>(clauses.size()))
    {
        clauses.resize(uid + 1);
    }

    clauses[uid] = clause;
}