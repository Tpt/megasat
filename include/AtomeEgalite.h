#ifndef ATOMEEgalite_H
#define ATOMEEgalite_H

#include "Terme.h"

//Représente xi = xj
class AtomeEgalite
{
public:
    AtomeEgalite();
    AtomeEgalite(unsigned int i, unsigned int j);
    unsigned int getI() const __attribute__((pure));
    unsigned int getJ() const __attribute__((pure));
    size_t hash() const __attribute__((pure));
    bool operator==(const AtomeEgalite& that) const __attribute__((pure));

private:
    unsigned int i;
    unsigned int j;
};

namespace std
{
    template<> struct hash<AtomeEgalite>
    {
        size_t operator()(const AtomeEgalite& atome) const
        {
            return atome.hash();
        }
    };
}

#endif // ATOMEEgalite_H
