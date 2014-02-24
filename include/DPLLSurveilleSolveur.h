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
    std::unordered_map<int,std::pair<int,int>> literauxSurveilles;
    bool assigneVariableEtRetourneSatisfiabilite(int varId, bool val);
    void initialiserLiterauxSurveilles();
    int trouveLiteralASurveille(Clause* clause, int autreLiteral = 0); /// Mettre autreLiteral à 0 quand il n'y a pas encore de literal surveillé. Retourne autreLiteral si, et seulement si, aucun autre litéral convenable n'est trouvé
    void onLiteralAssigne(int literalId);
    void assigneLiteralAFauxDansClause(Clause* clause, int literalId);
};

#endif