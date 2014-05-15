#include "../include/AtomeEgalite.h"
#include <functional>

using namespace std;

AtomeEgalite::AtomeEgalite() : i(0), j(0)
{}

AtomeEgalite::AtomeEgalite(unsigned int i_, unsigned int j_) : i(i_), j(j_)
{}

unsigned int AtomeEgalite::getI() const
{
    return i;
}

unsigned int AtomeEgalite::getJ() const
{
    return j;
}

size_t AtomeEgalite::hash() const
{
    return std::hash<unsigned int>()(i) + std::hash<unsigned int>()(j);
}

bool AtomeEgalite::operator==(const AtomeEgalite& that) const
{
    return (this->i == that.i && this->j == that.j) || (this->i == that.j && this->j == that.i);
}
