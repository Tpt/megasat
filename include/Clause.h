#ifndef CLAUSE_H
#define CLAUSE_H

#include<vector>
#include<string>
#include<sstream>
#include<unordered_set>
#include<list>
#include "Literal.h"
#include "Polarite.h"

class Clause
{
public:
    Clause(int variableNumber);
    Clause(int variableNumber, int uid);
    int size() const __attribute__((pure));
    bool simplificationUnitaire() const;
    bool isVide() const __attribute__((pure));
    int eval() const __attribute__((pure));
    int indiceMax() const __attribute__((pure));
    bool literalPresent(Literal* literal) const __attribute__((pure));
    void literauxPresents(std::vector<bool>& found_pos, std::vector<bool>& found_neg) const __attribute__((pure));
    void literalPresent(int id, bool& found_pos, bool& found_neg) const;
    bool isTautologie() const __attribute__((pure));
    void addLiteral(Literal* literal);
    void addLiteraux(std::unordered_set<Literal*> nouveauxLiteraux);
    void fusionner(Clause* c);
    std::unordered_set<Literal*> getLiteraux() const;
    void supprimerLiteraux(std::list<Literal*> literauxASupprimer);
    void supprimer(Literal* l);
    Polarite polariteLiteral(int id) const __attribute__((pure));
    void print() const;
    int getNombreDeVariables() const __attribute__((pure));
    bool estSurclause(const Clause* c) const;
    bool contientLiteralVrai() const __attribute__((pure));
    void supprimerLiterauxFaux();
    int getUid() const __attribute__((pure));

    static int genUid();
    static int nextUid;

private:
    std::unordered_set<Literal*> literaux;
    int variableNumber;
    int uid;
};

bool operator==(Clause const& a_, Clause const& b_);

#endif // CLAUSE_H
