#ifndef THEORIEGREFFONCONGRUENCE_H
#define THEORIEGREFFONCONGRUENCE_H

#include "TheorieGreffon.h"
#include "AtomeCongruence.h"
#include<map>

class TheorieGreffonCongruence : public TheorieGreffon
{
public:
    TheorieGreffonCongruence();
    TheorieGreffonCongruence(const TheorieGreffonCongruence& F);///Obligatoire pour pouvoir utiliser un attribut pointeur
    TheorieGreffonCongruence& operator=(const TheorieGreffonCongruence& F);///Idem
    virtual ~TheorieGreffonCongruence();
    virtual std::vector<int> onAssignation(int id, int niveau);
    virtual void onBacktrack(int l);
    virtual void onBeginning(Formule* formule);

private:
    bool appear(int variable, Terme* terme) const;
    Terme* replace(int variable, Terme* u, Terme* filtre) const;
    std::map<int, Terme> unify(Terme gauche, Terme droite) const;
    std::map<int, Terme> iterate(std::map<int, Terme> subst, std::vector<std::pair<Terme*, Terme*>> contraintes) const;

    Formule* formule;
    std::vector<AtomeCongruence> atomes;
    std::vector<std::map<int, Terme>> substitutions;
};

class nonUnifiableException : public std::exception
{};
#endif // THEORIEGREFFONCONGRUENCE_H
