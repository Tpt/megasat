#include "../include/AtomeDifference.h"
#include <functional>

using namespace std;

AtomeDifference::AtomeDifference() : i(0), j(0), n(0)
{}

AtomeDifference::AtomeDifference(unsigned int i_, unsigned int j_, int n_) : i(i_), j(j_), n(n_)
{}

unsigned int AtomeDifference::getI() const
{
    return i;
}

unsigned int AtomeDifference::getJ() const
{
    return j;
}

int AtomeDifference::getN() const
{
    return n;
}

size_t AtomeDifference::hash() const
{
    return std::hash<unsigned int>()(i)*31 + std::hash<unsigned int>()(j)*31*31 + std::hash<int>()(n)*31*31*31;
}

bool AtomeDifference::operator==(const AtomeDifference& that) const
{
    return this->i == that.i && this->j == that.j && this->n == that.n;
}
