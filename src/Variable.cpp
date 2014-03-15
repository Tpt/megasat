#include "../include/Variable.h"

using namespace std;

Variable::Variable(int id_) : id(id_), assigned(false), val(false)
{}

void Variable::setVal(bool e)
{
    assigned = true;
    val = e;
}

bool Variable::isAssignee() const
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

ResultatEvaluation Variable::eval() const
{
    if(!assigned)
        return INCONNU;
    return val ? VRAI : FAUX;
}
