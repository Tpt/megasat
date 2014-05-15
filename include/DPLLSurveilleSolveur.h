#ifndef DPLLSurveilleSolveur_H
#define DPLLSurveilleSolveur_H

#include<unordered_map>
#include "AbstractDPLLSolveur.h"

class DPLLSurveilleSolveur : public AbstractDPLLSolveur
{
public:
    DPLLSurveilleSolveur(Formule& formule, VariableNonAssigneeProvider& variableNonAssigneeProvider, GestionConflits& gestionConflits, TheorieGreffon& theorieGreffon);
    bool isSatifiable();
private:
    std::unordered_map<int,std::pair<int,int>> literauxSurveilles; //on ne peut stocker des Literal* car il changent lors d'un backtrack
    void assigneLiteral(int literalId);
    void initialiserLiterauxSurveilles();
    Literal* trouveLiteralASurveille(Clause* clause, Literal* autreLiteral = nullptr); /// Mettre autreLiteral à nullptr quand il n'y a pas encore de literal surveillé. Retourne autreLiteral si, et seulement si, aucun autre litéral convenable n'est trouvé
    void onLiteralAssigne(Literal* literal);
    void assigneLiteralAFauxDansClause(Clause* clause, int literalId, int autreLiteralId);
    virtual Clause* addClause(std::vector<int> clause, int uid);
    void initialiseClauseWatchedLiterals(Clause* clause);
    void TPropagation();
};

#endif
