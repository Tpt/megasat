#ifndef CLAUSE_H
#define CLAUSE_H

#include<vector>
#include<string>
#include<sstream>
#include<unordered_set>
#include"Literal.h"

class Clause
{
public:
    Clause(int variableNumber);
    int size() const;
    bool simplificationUnitaire() const;
    bool isVide() const;
    int eval() const;
    int indiceMax() const;
    void literauxPresents(std::vector<bool>& found_pos, std::vector<bool>& found_neg) const;
    void literalPresent(int id, bool& found_pos, bool& found_neg) const;
    bool isTautologie() const;
    void addLiteral(Literal* literal);
    void fusionner(Clause* c);
    std::unordered_set<Literal*> getLiteraux() const;
    void supprimer(Literal* l);
    int polariteLiteral(Literal* l1, Literal* l2) const;
    void print() const;
    int getV() const;
    int getVariableNumber() const;
    bool estSurclause(const Clause* c) const;
    bool contientLiteralVrai() const;
    void supprimerLiterauxFaux();

private:
    std::unordered_set<Literal*> literaux;
    int variableNumber;
};

bool operator==(Clause const& a_, Clause const& b_);
bool egalite_clauses(Clause const* a, Clause const* b);

bool comp(const Literal* a, const Literal* b);
bool comp_lit(const Literal* a, const Literal* b);

#endif // CLAUSE_H
