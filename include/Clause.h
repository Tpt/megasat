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
    Clause();
    Clause(std::unordered_set<Literal*> e, int V_e);
    ~Clause();
    Clause(const Clause& other);
    int size() const;
    bool isVide() const;
    int eval() const;
    int indiceMax() const;
    void literauxPresents(std::vector<bool>& found_pos, std::vector<bool>& found_neg) const;
    void literalPresent(int id, bool& found_pos, bool& found_neg) const;
    bool isTautologie() const;
    void fusionner(Clause* c);
    std::unordered_set<Literal*> getLiteraux() const;
    void supprimer(Literal* l);
    int polariteLiteral(Literal* l1, Literal* l2) const;
    void print() const;
    int getV() const;
    bool estSurclause(const Clause* c) const;

private:
    std::unordered_set<Literal*> literaux;
    int V;
    int n;
};

bool operator==(Clause const& a_, Clause const& b_);
bool egalite_clauses(Clause const* a, Clause const* b);

bool comp(const Literal* a, const Literal* b);
bool comp_lit(const Literal* a, const Literal* b);

#endif // CLAUSE_H
