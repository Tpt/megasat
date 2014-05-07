#ifndef THEORIEGREFFONCONGRUENCE_H
#define THEORIEGREFFONCONGRUENCE_H

#include "TheorieGreffon.h"
#include "AtomeCongruence.h"
#include<map>

class TheorieGreffonCongruence : public TheorieGreffon
{
public:
    TheorieGreffonCongruence();
    virtual ~TheorieGreffonCongruence();
    virtual std::vector<int> onAssignation(int id, int niveau);
    virtual void onBacktrack(int l);

private:
    bool appear(int variable, Terme* terme) const;
    Terme* replace(int variable, Terme* u, Terme* filtre) const;
    std::map<int, Terme> unify(Terme gauche, Terme droite) const;
    std::map<int, Terme> iterate(std::map<int, Terme> subst, std::vector<std::pair<Terme*, Terme*>> contraintes) const;


    std::vector<AtomeCongruence> atomes;
    std::vector<std::map<int, Terme>> substitutions;
};

class nonUnifiableException : public std::exception
{};
#endif // THEORIEGREFFONCONGRUENCE_H
