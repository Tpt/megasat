#ifndef THEORIEGREFFONCONGRUENCE_H
#define THEORIEGREFFONCONGRUENCE_H

#include "TheorieGreffon.h"
#include "AtomeCongruence.h"
#include<map>

class TheorieGreffonCongruence : public TheorieGreffonSimple
{
public:
    TheorieGreffonCongruence();
    TheorieGreffonCongruence(const TheorieGreffonCongruence& F);///Obligatoire pour pouvoir utiliser un attribut pointeur
    TheorieGreffonCongruence& operator=(const TheorieGreffonCongruence& F);///Idem
    virtual ~TheorieGreffonCongruence();
    virtual std::vector<int> onAssignation(int id, unsigned int niveau);
    virtual void onBacktrack(unsigned int l);
    void setCorrespondanceAtomes(const std::vector<AtomeCongruence>& corr) {atomes=corr;};

private:
    bool appear(int variable, Terme* terme) const;
    Terme* replace(int variable, Terme* u, Terme* filtre) const;
    std::map<int, Terme> unify(AtomeCongruence atome) const;
    std::map<int, Terme> unify(Terme gauche, Terme droite) const;
    std::map<int, Terme> iterate(std::map<int, Terme> subst, std::vector<std::pair<Terme*, Terme*>> contraintes) const;
    AtomeCongruence appliquerSubstitutions(unsigned int id) const;
    Terme* appliquerSubstitutions(Terme terme) const;
    Terme* appliquerSubstitutions(Terme* terme) const;

    std::vector<AtomeCongruence> atomes;
    std::vector<std::map<int, Terme>> substitutions;
};

class nonUnifiableException : public std::exception
{};
#endif // THEORIEGREFFONCONGRUENCE_H
