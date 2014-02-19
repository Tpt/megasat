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
    void addLiteraux(std::unordered_set<Literal*> nouveauxLiteraux);
    void fusionner(Clause* c);
    std::unordered_set<Literal*> getLiteraux() const;
    void supprimer(Literal* l);
    int polariteLiteral(int id) const;
    void print() const;
    int getNombreDeVariables() const;
    bool estSurclause(const Clause* c) const;
    bool contientLiteralVrai() const;
    void supprimerLiterauxFaux();

private:
    std::unordered_set<Literal*> literaux;
    int variableNumber;
};

bool operator==(Clause const& a_, Clause const& b_);

#endif // CLAUSE_H
