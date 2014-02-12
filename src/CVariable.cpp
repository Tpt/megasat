#include "CVariable.h"

using namespace std;

CVariable::~CVariable()
{}

CVariable::CVariable() : id(0), assigned(false), val(false)
{}

void CVariable::setVal(bool e)
{
    assigned=true;
    val=e;
}

bool CVariable::isAssigned() const
{
    return assigned;
}

bool CVariable::getVal() const
{
    return val;
}

bool CVariable::less(CVariable const& b) const
{
    return id<b.id;
}

bool CVariable::eless(CVariable const& b) const
{
    return id<=b.id;
}

int CVariable::getId() const
{
    return id;
}

CVariable::CVariable(int id_e) : id(id_e), assigned(false), val(false)
{}

CVariable::CVariable(const CVariable& other) : id(other.id), assigned(other.assigned), val(other.val)
{}

bool operator<(int const a, CVariable const& b)
{
    return a<b.getId();
}

bool operator<(CVariable const &a, int const b)
{
    return a.getId()<b;
}

bool operator<(CVariable const &a, CVariable const& b)
{
    return a.less(b);
}

bool operator>(int const a, CVariable const& b)
{
    return a>b.getId();
}

bool operator>(CVariable const &a, int const b)
{
    return a.getId()>b;
}

bool operator>(CVariable const &a, CVariable const& b)
{
    return b.less(a);
}

bool operator<=(int const a, CVariable const& b)
{
    return a<=b.getId();
}

bool operator<=(CVariable const &a, int const b)
{
    return a.getId()<=b;
}

bool operator<=(CVariable const &a, CVariable const& b)
{
    return a.eless(b);
}

bool operator>=(int const a, CVariable const& b)
{
    return a>=b.getId();
}

bool operator>=(CVariable const &a, int const b)
{
    return a.getId()>=b;
}

bool operator>=(CVariable const &a, CVariable const& b)
{
    return b.eless(a);
}

bool operator==(CVariable const &a, CVariable const& b)
{
    return a.getId()==b.getId();
}

bool operator==(int const a, CVariable const& b)
{
    return a==b.getId();
}

bool operator==(CVariable const &a, int const b)
{
    return a.getId()==b;
}

bool operator!=(CVariable const &a, CVariable const& b)
{
    return !(a==b);
}

bool operator!=(int const a, CVariable const& b)
{
    return !(a==b);
}

bool operator!=(CVariable const &a, int const b)
{
    return !(a==b);
}
