#ifndef VariableNonAssigneeProvider_H
#define VariableNonAssigneeProvider_H

#include "Formule.h"

class VariableNonAssigneeProvider
{
public:
    ~VariableNonAssigneeProvider() {}
    virtual std::pair<int, bool> getVariableNonAssignee(const Formule& formule) const = 0; //retourne une variable non assignée
};

class VariableNonAssigneeProviderSimple : public VariableNonAssigneeProvider
{
public:
    std::pair<int, bool> getVariableNonAssignee(const Formule& formule) const;
};

class VariableNonAssigneeProviderRand : public VariableNonAssigneeProvider
{
public:
    std::pair<int, bool> getVariableNonAssignee(const Formule& formule) const;
};

class VariableNonAssigneeProviderMalin : public VariableNonAssigneeProvider
{
public:
    std::pair<int, bool> getVariableNonAssignee(const Formule& formule) const;
};

class VariableNonAssigneeProviderMOMS : public VariableNonAssigneeProvider
{
public:
    std::pair<int, bool> getVariableNonAssignee(const Formule& formule) const;
};

class VariableNonAssigneeProviderDLIS : public VariableNonAssigneeProvider
{
public:
    std::pair<int, bool> getVariableNonAssignee(const Formule& formule) const;
};

#endif
