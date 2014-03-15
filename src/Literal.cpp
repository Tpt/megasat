#include "../include/Literal.h"
#include<iostream>

using namespace std;

Literal::Literal(Variable* var_, bool polarite_) : var(var_), polarite(polarite_)
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

bool Literal::isAssigne() const
{
    return var->isAssignee();
}

bool Literal::getVal() const
{
    return polarite ? var->getVal() : !var->getVal();
}

ResultatEvaluation Literal::eval() const
{
    if(!var->isAssignee())
        return INCONNU;
    return getVal() ? VRAI : FAUX;
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