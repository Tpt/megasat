#ifndef DPLLSurveilleSolveur_H
#define DPLLSurveilleSolveur_H

#include<unordered_map>
#include"AbstractDPLLSolveur.h"

class DPLLSurveilleSolveur : public AbstractDPLLSolveur
{
public:
    DPLLSurveilleSolveur(Formule &formule);
    bool isSatifiable();
private:
    std::unordered_map<int,std::pair<int,int>> literauxSurveilles; //on ne peut stocker des Literal* car il changent lors d'un backtrack
    bool assigneVariableEtRetourneSatisfiabilite(int varId, bool val);
    void initialiserLiterauxSurveilles();
    Literal* trouveLiteralASurveille(Clause* clause, Literal* autreLiteral = nullptr); /// Mettre autreLiteral à nullptr quand il n'y a pas encore de literal surveillé. Retourne autreLiteral si, et seulement si, aucun autre litéral convenable n'est trouvé
    bool onLiteralAssigne(int literalId); //retourne si tout se passe bien (ie pas trouvé de clauses insatisfiable
    bool assigneLiteralAFauxDansClauseEtRetourneEtat(Clause* clause, int literalId, int autreLiteralId);
};

#endif