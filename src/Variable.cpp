#include "../include/Variable.h"

using namespace std;

Variable::~Variable()
{}

Variable::Variable() : id(0), assigned(false), val(false)
{}

Variable::Variable(int id) : id(id), assigned(false), val(false)
{}

Variable::Variable(const Variable& other) : id(other.id), assigned(other.assigned), val(other.val)
{}

void Variable::setVal(bool e)
{
    assigned = true;
    val = e;
}

bool Variable::isAssigned() const
{
    return assigned;
}

bool Variable::getVal() const
{
    return val;
}

int Variable::getId() const
{
    return id;
}

bool operator<(int const a, Variable const& b)
{
    return a < b.getId();
}

bool operator<(Variable const &a, int const b)
{
    return a.getId() < b;
}

bool operator<(Variable const &a, Variable const& b)
{
    return a.getId() < b.getId();
}

bool operator>(int const a, Variable const& b)
{
    return a > b.getId();
}

bool operator>(Variable const &a, int const b)
{
    return a.getId() > b;
}

bool operator>(Variable const &a, Variable const& b)
{
    return a.getId() > b.getId();
}

bool operator<=(int const a, Variable const& b)
{
    return a <= b.getId();
}

bool operator<=(Variable const &a, int const b)
{
    return a.getId() <= b;
}

bool operator<=(Variable const &a, Variable const& b)
{
    return a.getId() < b.getId();
}

bool operator>=(int const a, Variable const& b)
{
    return a >= b.getId();
}

bool operator>=(Variable const &a, int const b)
{
    return a.getId() >= b;
}

bool operator>=(Variable const &a, Variable const& b)
{
    return a.getId() < b.getId();
}

bool operator==(Variable const &a, Variable const& b)
{
    return a.getId() == b.getId();
}

bool operator==(int const a, Variable const& b)
{
    return a == b.getId();
}

bool operator==(Variable const &a, int const b)
{
    return a.getId() == b;
}

bool operator!=(Variable const &a, Variable const& b)
{
    return a.getId() != b.getId();
}

bool operator!=(int const a, Variable const& b)
{
    return a != b.getId();
}

bool operator!=(Variable const &a, int const b)
{
    return a.getId() != b;
}
