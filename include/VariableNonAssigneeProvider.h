#ifndef VariableNonAssigneeProvider_H
#define VariableNonAssigneeProvider_H

#include "Formule.h"

class VariableNonAssigneeProvider
{
public:
    virtual ~VariableNonAssigneeProvider() {}
    virtual int getVariableNonAssignee(const Formule& formule) const = 0; //retourne une variable non assignée
};

class VariableNonAssigneeProviderSimple : public VariableNonAssigneeProvider
{
public:
    int getVariableNonAssignee(const Formule& formule) const;
};

class VariableNonAssigneeProviderRand : public VariableNonAssigneeProvider
{
public:
    VariableNonAssigneeProviderRand();
    int getVariableNonAssignee(const Formule& formule) const;
};

class VariableNonAssigneeProviderMalin : public VariableNonAssigneeProviderRand
{
public:
    int getVariableNonAssignee(const Formule& formule) const;
};

class VariableNonAssigneeProviderMOMS : public VariableNonAssigneeProvider
{
public:
    int getVariableNonAssignee(const Formule& formule) const;
};

class VariableNonAssigneeProviderDLIS : public VariableNonAssigneeProvider
{
public:
    int getVariableNonAssignee(const Formule& formule) const;
};

class PlusDeVariablesAAssigner : public std::exception
{};

#endif
