#include "../include/GestionConflits.h"
#include "../include/GraphvizConflitOutput.h"
#include "../include/LatexPrinter.h"
#include<iostream>
#include<algorithm>

using namespace std;

GestionConflits::GestionConflits(int prochainConflit_)
: conflitsNum(0), prochainConflit(prochainConflit_)
{}

GestionConflits::~GestionConflits()
{}

void GestionConflits::onBeginning(Formule* formule)
{}

void GestionConflits::onDeduction(Literal* literal, int clauseUid, int profondeurPile)
{}

void GestionConflits::onChoix(int literalId, int profondeurPile)
{}

void GestionConflits::onBacktrack(int nouvelleProfondeur)
{}

void GestionConflits::addClause(std::vector<int>& clause, int uid)
{}

pair<int,pair<int,vector<int>>> GestionConflits::onConflit(int clauseUid, int profondeurPile)
{
    conflitsNum++;
    return pair<int,pair<int,vector<int>>>(0, pair<int,vector<int>>(-1, vector<int>(0)));
}

void GestionConflits::afficheStatistiques(std::streambuf* sortie, const string& debutCommentaire) const
{}


GestionConflitsStatistiques::GestionConflitsStatistiques() : nombreVraiBacktrack(0), profondeurCumuleBacktracks(0), nombreClausesAjoutes(0), tailleCumuleAjouts(0)
{}

void GestionConflitsStatistiques::onBacktrack(int profondeur)
{
    if(profondeur > 0) {
        nombreVraiBacktrack++;
        profondeurCumuleBacktracks += profondeur;
    }
}

void GestionConflitsStatistiques::onAjoutClause(unsigned long tailleClause)
{
    nombreClausesAjoutes++;
    tailleCumuleAjouts += tailleClause;
}

void GestionConflitsStatistiques::afficheStatistiques(std::streambuf* sortie, const string& debutCommentaire) const
{
    ostream out(sortie);
    out << debutCommentaire << " Nombre de backtrack de profondeur supérieure à 1 : " << nombreVraiBacktrack << endl;
    out << debutCommentaire << " Profondeur moyenne des backtracks : " << (((float) profondeurCumuleBacktracks) / nombreVraiBacktrack) + 1 << endl;
    out << debutCommentaire << " Taille moyenne des clauses ajoutées : " << ((float) tailleCumuleAjouts) / nombreClausesAjoutes << endl;
}



GestionConflitsApprentissage::GestionConflitsApprentissage(int prochainConflit_)
 : GestionConflits(prochainConflit_), clauses(vector<vector<int>>()), pileDeDeductions(vector<pair<int,vector<int>>>()), niveauChoix(vector<int>()), statistiques(GestionConflitsStatistiques())
{}

void GestionConflitsApprentissage::onBeginning(Formule* formule)
{
    clauses = vector<vector<int>>();
    for(Clause* clause : formule->getClauses())
    {
        addClause(clause);
    }
    niveauChoix = vector<int>(formule->getNombreDeVariables(), -1);
    for(Variable* var : formule->getVars())
        if(var->isAssignee())
            niveauChoix[var->getId() - 1] = 0;
    statistiques = GestionConflitsStatistiques();
}

void GestionConflitsApprentissage::onDeduction(Literal* literal, int clauseUid, int profondeurPile)
{
    pileDeDeductions.push_back(pair<int,vector<int>>(literal->getId(), clauses[clauseUid]));
    niveauChoix[literal->getAbsId() - 1] = profondeurPile;
}

void GestionConflitsApprentissage::onChoix(int literalId, int profondeurPile)
{
    pileDeDeductions = vector<pair<int,vector<int>>>();
    pileDeDeductions.push_back(pair<int,vector<int>>(literalId, vector<int>(0)));
    niveauChoix[abs(literalId) - 1] = profondeurPile;
}

pair<int,pair<int,vector<int>>> GestionConflitsApprentissage::onConflit(int clauseUid, int profondeurPile)
{
    GestionConflits::onConflit(clauseUid, profondeurPile);

    int literalConflictuel = getLiteralConflictuel(clauseUid);
    pileDeDeductions.push_back(pair<int,vector<int>>(literalConflictuel, clauses[clauseUid]));
    ConstructeurPreuve constructeurPreuve(pileDeDeductions);

    if(conflitsNum == prochainConflit)
        displayInterface(constructeurPreuve);

    int uid = Clause::genUid();
    vector<int> clauseAAjouter = constructeurPreuve.getNouvelleClause();

    int niveauBacktrack = getNiveauBacktrack(clauseAAjouter);
    int nombreDeBacktraks = profondeurPile - niveauBacktrack - 1;
#ifdef DEBUG
    cout << "c Backtrack de : " << nombreDeBacktraks << endl;
#endif
    statistiques.onAjoutClause(clauseAAjouter.size());
    statistiques.onBacktrack(nombreDeBacktraks);

    return pair<int,pair<int,vector<int>>>(nombreDeBacktraks, pair<int,vector<int>>(uid, clauseAAjouter));
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

void GestionConflitsApprentissage::afficheStatistiques(std::streambuf* sortie, const string& debutCommentaire) const
{
    statistiques.afficheStatistiques(sortie, debutCommentaire);
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

void GestionConflitsApprentissage::addClause(vector<int>& clause, int uid)
{
    if(uid >= static_cast<int>(clauses.size()))
    {
        clauses.resize(uid + 1);
    }

    clauses[uid] = clause;
}

int GestionConflitsApprentissage::getNiveauBacktrack(const vector<int>& clause) const
{
    if(clause.size() <= 1)
        return 0;

    vector<int> profondeurs(clause.size());
    for(unsigned int i = 0; i < clause.size(); i++) {
        profondeurs[i] = niveauChoix[abs(clause[i]) - 1];
    }
    sort(profondeurs.begin(), profondeurs.end());

    return profondeurs[profondeurs.size() - 2];
}

void GestionConflitsApprentissage::onBacktrack(int niveauFutur)
{
    for(auto& niveau : niveauChoix)
    {
        if(niveau >= niveauFutur)
            niveau = -1;
    }
}
