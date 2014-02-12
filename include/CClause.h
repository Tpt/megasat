#ifndef CCLAUSE_H
#define CCLAUSE_H

#include<vector>
#include<string>
#include<sstream>
#include<unordered_set>
#include"CLiteral.h"

class CClause
{
    public:
    CClause();
    CClause(std::unordered_set<CLiteral*> e, int V_e);
    ~CClause();
    CClause(const CClause& other);
    int size() const;
    bool isVide() const;
    int eval() const;
    int indiceMax() const;
    void literauxPresents(std::vector<bool>& found_pos, std::vector<bool>& found_neg) const;
    void literalPresent(int id, bool& found_pos, bool& found_neg) const;
    bool isTautologie() const;
    void fusionner(CClause* c);
    std::unordered_set<CLiteral*> getLiteraux() const;
    void supprimer(CLiteral* l);
    int polariteLiteral(CLiteral* l1, CLiteral* l2) const;
    void print() const;
    int getV() const;
    bool estSurclause(const CClause* c) const;

    private:
    std::unordered_set<CLiteral*> literaux;
    int V;
    int n;
};

bool operator==(CClause const& a_, CClause const& b_);
bool egalite_clauses(CClause const* a, CClause const* b);

bool comp(const CLiteral* a, const CLiteral* b);
bool comp_lit(const CLiteral* a, const CLiteral* b);

#endif // CCLAUSE_H
