#include "CLiteral.h"
#include<iostream>

using namespace std;

CLiteral::~CLiteral()
{}

CLiteral::CLiteral() : var(NULL), polarite(true)
{}

void CLiteral::setVal(bool e) /** Agit sur la variable pointee **/
{
    if(polarite)
        var->setVal(e);
    else
        var->setVal(!e);
}

void CLiteral::print() const
{
    if(!polarite)
        cout<<"-";
    cout<<var->getId();
}

CVariable* CLiteral::getVar() const
{
    return var;
}

bool CLiteral::getPolarite() const
{
    return polarite;
}

bool CLiteral::isAssigned() const
{
    return var->isAssigned();
}

bool CLiteral::getVal() const
{
    return polarite ? var->getVal() : !var->getVal();
}

int CLiteral::getAbsId() const
{
    return var->getId();
}

int CLiteral::getId() const
{
    return polarite ? var->getId() : -(var->getId());
}

bool CLiteral::less(CLiteral const& b) const
{
    return getAbsId()<b.getAbsId();
}

bool CLiteral::eless(CLiteral const& b) const
{
    return getAbsId()<=b.getAbsId();
}

CLiteral::CLiteral(CVariable* a, bool pol) : var(a), polarite(pol)
{}

CLiteral::CLiteral(const CLiteral& other) : var(other.var), polarite(other.polarite)
{}

CLiteral& CLiteral::operator=(const CLiteral& rhs)
{
    if (this == &rhs) return *this;

    var=rhs.var;
    polarite=rhs.polarite;

    return *this;
}

bool operator<(int const a, CLiteral const& b)
{
    return a<b.getAbsId();
}

bool operator<(CLiteral const &a, int const b)
{
    return a.getAbsId()<b;
}

bool operator<(CLiteral const &a, CLiteral const& b)
{
    return a.less(b);
}

bool operator>(int const a, CLiteral const& b)
{
    return a>b.getAbsId();
}

bool operator>(CLiteral const &a, int const b)
{
    return a.getAbsId()>b;
}

bool operator>(CLiteral const &a, CLiteral const& b)
{
    return b.less(a);
}

bool operator<=(int const a, CLiteral const& b)
{
    return a<=b.getAbsId();
}

bool operator<=(CLiteral const &a, int const b)
{
    return a.getAbsId()<=b;
}

bool operator<=(CLiteral const &a, CLiteral const& b)
{
    return a.eless(b);
}

bool operator>=(int const a, CLiteral const& b)
{
    return a>=b.getAbsId();
}

bool operator>=(CLiteral const &a, int const b)
{
    return a.getAbsId()<b;
}

bool operator>=(CLiteral const &a, CLiteral const& b)
{
    return b.eless(a);
}

bool operator==(int const a, CLiteral const& b)
{
    return b.getId()==a;
}

bool operator==(CLiteral const &a, int const b)
{
    return a.getId()==b;
}

bool operator==(CLiteral const &a, CLiteral const& b)
{
    return a.getId()==b.getId();
}

bool operator!=(int const a, CLiteral const& b)
{
    return !(a==b);
}

bool operator!=(CLiteral const &a, int const b)
{
    return !(a==b);
}

bool operator!=(CLiteral const &a, CLiteral const& b)
{
    return !(a==b);
}
