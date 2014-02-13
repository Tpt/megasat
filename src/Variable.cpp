#include "../include/Variable.h"

using namespace std;

Variable::~Variable()
{}

Variable::Variable() : id(0), assigned(false), val(false)
{}

void Variable::setVal(bool e)
{
    assigned=true;
    val=e;
}

bool Variable::isAssigned() const
{
    return assigned;
}

bool Variable::getVal() const
{
    return val;
}

bool Variable::less(Variable const& b) const
{
    return id<b.id;
}

bool Variable::eless(Variable const& b) const
{
    return id<=b.id;
}

int Variable::getId() const
{
    return id;
}

Variable::Variable(int id_e) : id(id_e), assigned(false), val(false)
{}

Variable::Variable(const Variable& other) : id(other.id), assigned(other.assigned), val(other.val)
{}

bool operator<(int const a, Variable const& b)
{
    return a<b.getId();
}

bool operator<(Variable const &a, int const b)
{
    return a.getId()<b;
}

bool operator<(Variable const &a, Variable const& b)
{
    return a.less(b);
}

bool operator>(int const a, Variable const& b)
{
    return a>b.getId();
}

bool operator>(Variable const &a, int const b)
{
    return a.getId()>b;
}

bool operator>(Variable const &a, Variable const& b)
{
    return b.less(a);
}

bool operator<=(int const a, Variable const& b)
{
    return a<=b.getId();
}

bool operator<=(Variable const &a, int const b)
{
    return a.getId()<=b;
}

bool operator<=(Variable const &a, Variable const& b)
{
    return a.eless(b);
}

bool operator>=(int const a, Variable const& b)
{
    return a>=b.getId();
}

bool operator>=(Variable const &a, int const b)
{
    return a.getId()>=b;
}

bool operator>=(Variable const &a, Variable const& b)
{
    return b.eless(a);
}

bool operator==(Variable const &a, Variable const& b)
{
    return a.getId()==b.getId();
}

bool operator==(int const a, Variable const& b)
{
    return a==b.getId();
}

bool operator==(Variable const &a, int const b)
{
    return a.getId()==b;
}

bool operator!=(Variable const &a, Variable const& b)
{
    return !(a==b);
}

bool operator!=(int const a, Variable const& b)
{
    return !(a==b);
}

bool operator!=(Variable const &a, int const b)
{
    return !(a==b);
}
