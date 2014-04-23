#ifndef CONSTRUCTEURPREUVE_H
#define CONSTRUCTEURPREUVE_H

#include "Preuve.h"

class ConstructeurPreuve
{
public:
    ConstructeurPreuve(std::vector<std::pair<int,std::vector<int>>> graphe);
    ~ConstructeurPreuve();
    std::vector<int> getNouvelleClause() const {return preuve.getConclusion();};
    Preuve getPreuve() const {return preuve;};

private:
    Preuve construirePreuve() const;
    std::vector<int> variablesNiveauCourant() const;
    std::vector<int> variablesNiveauCourantRestantes(const std::vector<int>& variables, const std::vector<int>& clause) const;
    std::vector<int> rechercherClauseAssignantLiteral(int id) const;


    std::vector<std::pair<int,std::vector<int>>> graphe;
    Preuve preuve;

};

#endif // CONSTRUCTEURPREUVE_H
