#include "../include/AtomeDifference.h"
#include <functional>

using namespace std;

AtomeDifference::AtomeDifference() : i(-1), j(-1), n(0)
{}

AtomeDifference::AtomeDifference(int i_, int j_, int n_) : i(i_), j(j_), n(n_)
{}

int AtomeDifference::getI() const
{
    return i;
}

int AtomeDifference::getJ() const
{
    return j;
}

int AtomeDifference::getN() const
{
    return j;
}

size_t AtomeDifference::hash() const
{
    return std::hash<int>()(i)*31 + std::hash<int>()(j)*31*31 + std::hash<int>()(n)*31*31*31;
}

bool AtomeDifference::operator==(const AtomeDifference& that) const
{
    return this->i == that.i && this->j == that.j && this->n == that.n;
}
