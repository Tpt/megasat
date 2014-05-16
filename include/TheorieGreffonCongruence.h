#ifndef THEORIEGREFFONCONGRUENCE_H
#define THEORIEGREFFONCONGRUENCE_H

#include "TheorieGreffon.h"
#include "AtomeCongruence.h"
#include<map>

class TheorieGreffonCongruence : public TheorieGreffonSimple
{
public:
    TheorieGreffonCongruence();
    virtual ~TheorieGreffonCongruence();
    virtual std::vector<int> onAssignation(int id, unsigned int niveau);
    virtual void onBacktrack(unsigned int l);
    void setCorrespondanceAtomes(const std::vector<AtomeCongruence>& corr) {atomes=corr;};
    std::vector<std::map<int, Terme>> getSubstitutions() const {return substitutions;};

private:
    bool appear(int variable, const Terme& terme) const;
    Terme replace(int variable, const Terme& u, const Terme& filtre) const;
    std::map<int, Terme> unify(const AtomeCongruence& atome) const;
    std::map<int, Terme> unify(const Terme& gauche, const Terme& droite) const;
    std::map<int, Terme> iterate(const std::map<int, Terme>& subst, std::vector<std::pair<Terme, Terme>> contraintes) const;
    AtomeCongruence appliquerSubstitutions(unsigned int id) const;
    Terme appliquerSubstitutions(const Terme terme) const;

    std::vector<AtomeCongruence> atomes;
    std::vector<std::map<int, Terme>> substitutions;
};

class nonUnifiableException : public std::exception
{};
#endif // THEORIEGREFFONCONGRUENCE_H
