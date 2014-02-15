#include "../include/Literal.h"
#include<iostream>

using namespace std;

Literal::~Literal()
{}

Literal::Literal() : var(NULL), polarite(true)
{}

Literal::Literal(Variable* a, bool pol) : var(a), polarite(pol)
{}

Literal::Literal(const Literal& other) : var(other.var), polarite(other.polarite)
{}

void Literal::setVal(bool e)
{
    if(polarite)
        var->setVal(e);
    else
        var->setVal(!e);
}

void Literal::print() const
{
    if(!polarite)
        cout << "-";
    cout << var->getId();
}

Variable* Literal::getVar() const
{
    return var;
}

bool Literal::getPolarite() const
{
    return polarite;
}

bool Literal::isAssigned() const
{
    return var->isAssigned();
}

bool Literal::getVal() const
{
    return polarite ? var->getVal() : !var->getVal();
}

int Literal::getAbsId() const
{
    return var->getId();
}

int Literal::getId() const
{
    return polarite ? var->getId() : -(var->getId());
}

Literal& Literal::operator=(const Literal& rhs)
{
    if(this == &rhs)
        return *this;

    var = rhs.var;
    polarite = rhs.polarite;

    return *this;
} //TODO: utile ???


bool operator<(int const a, Literal const& b)
{
    return a < b.getAbsId();
}

bool operator<(Literal const &a, int const b)
{
    return a.getAbsId() < b;
}

bool operator<(Literal const &a, Literal const& b)
{
    return a.getAbsId() < b.getAbsId();
}

bool operator>(int const a, Literal const& b)
{
    return a > b.getAbsId();
}

bool operator>(Literal const &a, int const b)
{
    return a.getAbsId() > b;
}

bool operator>(Literal const &a, Literal const& b)
{
    return a.getAbsId() > b.getAbsId();
}

bool operator<=(int const a, Literal const& b)
{
    return a <= b.getAbsId();
}

bool operator<=(Literal const &a, int const b)
{
    return a.getAbsId() <= b;
}

bool operator<=(Literal const &a, Literal const& b)
{
    return a.getAbsId() <= b.getAbsId();
}

bool operator>=(int const a, Literal const& b)
{
    return a >= b.getAbsId();
}

bool operator>=(Literal const &a, int const b)
{
    return a.getAbsId() >= b;
}

bool operator>=(Literal const &a, Literal const& b)
{
    return a.getAbsId() >= b.getAbsId();
}

bool operator==(int const a, Literal const& b)
{
    return b.getId() == a;
}

bool operator==(Literal const &a, int const b)
{
    return a.getId() == b;
}

bool operator==(Literal const &a, Literal const& b)
{
    return a.getId() == b.getId();
}

bool operator!=(int const a, Literal const& b)
{
    return a != b.getId();
}

bool operator!=(Literal const &a, int const b)
{
    return a.getId() != b;
}

bool operator!=(Literal const &a, Literal const& b)
{
    return a.getId() != b.getId();
}
