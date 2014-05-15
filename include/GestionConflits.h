#ifndef GestionConflits_H
#define GestionConflits_H

#include<vector>
#include "Formule.h"
#include "ConstructeurPreuve.h"

class GestionConflits
{
public:
    GestionConflits(int prochainConflit = 0);
    virtual ~GestionConflits();
    virtual void onBeginning(Formule* formule);
    virtual void onDeduction(Literal* literal, int clauseUid, int profondeurPile);
    virtual void onChoix(int literalId, int profondeurPile);
    virtual void onBacktrack(int niveauFutur);
    virtual void addClause(std::vector<int>& clause, int uid);
    virtual std::pair<int,std::pair<int,std::vector<int>>> onConflit(int clauseUid, int profondeurPile);
    virtual void afficheStatistiques(std::streambuf* sortie, const std::string& debutCommentaire) const;
    virtual bool isCompatibleAvecTPropagation() const {return true;};
protected:
    int conflitsNum;
    int prochainConflit;
};

class GestionConflitsStatistiques
{
public:
    GestionConflitsStatistiques();
    void onBacktrack(int profondeur);
    void onAjoutClause(unsigned long tailleClause);
    void afficheStatistiques(std::streambuf* sortie, const std::string& debutCommentaire) const;
private:
    int nombreVraiBacktrack;
    int profondeurCumuleBacktracks;
    int nombreClausesAjoutes;
    unsigned long tailleCumuleAjouts;
};

class GestionConflitsApprentissage : public GestionConflits
{
public:
    GestionConflitsApprentissage(int prochainConflit = 0);
    void onBeginning(Formule* formule);
    void onDeduction(Literal* literal, int clauseUid, int profondeurPile);
    void onChoix(int literal, int profondeurPile);
    void onBacktrack(int nouvelleProfondeur);
    void addClause(std::vector<int>& clause, int uid);
    std::pair<int,std::pair<int,std::vector<int>>> onConflit(int clauseUid, int profondeurPile);
    int getNiveauBacktrack(const std::vector<int>& clause) const;
    void afficheStatistiques(std::streambuf* sortie, const std::string& debutCommentaire) const;
    virtual bool isCompatibleAvecTPropagation() const {return false;};
private:
    void displayInterface(ConstructeurPreuve constructeurPreuve);
    void addClause(const Clause* clause);
    int getLiteralConflictuel(int clauseUid) const;
    void updateNiveauChoix();

    std::vector<std::vector<int>> clauses;
    std::vector<std::pair<int,std::vector<int>>> pileDeDeductions;
    std::vector<int> niveauChoix;
    GestionConflitsStatistiques statistiques;
};
#endif
