#ifndef ATOMEDifference_H
#define ATOMEDifference_H

#include "Terme.h"

//Représente xi - xj <= n
class AtomeDifference
{
public:
    AtomeDifference(int i, int j, int n);
    int getI() const __attribute__((pure));
    int getJ() const __attribute__((pure));
    int getN() const __attribute__((pure));
    size_t hash() const __attribute__((pure));
    bool operator==(const AtomeDifference& that) const __attribute__((pure));

private:
    int i;
    int j;
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
