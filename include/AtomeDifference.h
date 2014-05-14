#ifndef ATOMEDifference_H
#define ATOMEDifference_H

#include "Terme.h"

//Représente xi - xj <= n
//Note : On a la variable spéciale x-1 qui vaut toujours 0
class AtomeDifference
{
public:
    AtomeDifference();
    AtomeDifference(unsigned int i, unsigned int j, int n);
    unsigned int getI() const __attribute__((pure));
    unsigned int getJ() const __attribute__((pure));
    int getN() const __attribute__((pure));
    size_t hash() const __attribute__((pure));
    bool operator==(const AtomeDifference& that) const __attribute__((pure));

private:
    unsigned int i;
    unsigned int j;
    int n;
};

namespace std
{
    template<> struct hash<AtomeDifference>
    {
        size_t operator()(const AtomeDifference& atome) const
        {
            return atome.hash();
        }
    };
}

#endif // ATOMEDifference_H
