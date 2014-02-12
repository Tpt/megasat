#include "Literal.h"
#include<iostream>

using namespace std;

Literal::~Literal()
{}

Literal::Literal() : var(NULL), polarite(true)
{}

void Literal::setVal(bool e) /** Agit sur la variable pointee **/
{
    if(polarite)
        var->setVal(e);
    else
        var->setVal(!e);
}

void Literal::print() const
{
    if(!polarite)
        cout<<"-";
    cout<<var->getId();
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

bool Literal::less(Literal const& b) const
{
    return getAbsId()<b.getAbsId();
}

bool Literal::eless(Literal const& b) const
{
    return getAbsId()<=b.getAbsId();
}

Literal::Literal(Variable* a, bool pol) : var(a), polarite(pol)
{}

Literal::Literal(const Literal& other) : var(other.var), polarite(other.polarite)
{}

Literal& Literal::operator=(const Literal& rhs)
{
    if (this == &rhs) return *this;

    var=rhs.var;
    polarite=rhs.polarite;

    return *this;
}

bool operator<(int const a, Literal const& b)
{
    return a<b.getAbsId();
}

bool operator<(Literal const &a, int const b)
{
    return a.getAbsId()<b;
}

bool operator<(Literal const &a, Literal const& b)
{
    return a.less(b);
}

bool operator>(int const a, Literal const& b)
{
    return a>b.getAbsId();
}

bool operator>(Literal const &a, int const b)
{
    return a.getAbsId()>b;
}

bool operator>(Literal const &a, Literal const& b)
{
    return b.less(a);
}

bool operator<=(int const a, Literal const& b)
{
    return a<=b.getAbsId();
}

bool operator<=(Literal const &a, int const b)
{
    return a.getAbsId()<=b;
}

bool operator<=(Literal const &a, Literal const& b)
{
    return a.eless(b);
}

bool operator>=(int const a, Literal const& b)
{
    return a>=b.getAbsId();
}

bool operator>=(Literal const &a, int const b)
{
    return a.getAbsId()<b;
}

bool operator>=(Literal const &a, Literal const& b)
{
    return b.eless(a);
}

bool operator==(int const a, Literal const& b)
{
    return b.getId()==a;
}

bool operator==(Literal const &a, int const b)
{
    return a.getId()==b;
}

bool operator==(Literal const &a, Literal const& b)
{
    return a.getId()==b.getId();
}

bool operator!=(int const a, Literal const& b)
{
    return !(a==b);
}

bool operator!=(Literal const &a, int const b)
{
    return !(a==b);
}

bool operator!=(Literal const &a, Literal const& b)
{
    return !(a==b);
}
