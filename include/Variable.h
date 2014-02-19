#ifndef VARIABLE_H
#define VARIABLE_H

#include<vector>
#include"ResultatEvaluation.h"

class Variable
{
public:
    Variable(int id_);
    int getId() const;
    bool isAssignee() const;
    bool getVal() const;
    void setVal(bool e);
    ResultatEvaluation eval() const;

private:
    int id;         /// Le numéro de la variable
    bool assigned;  /// Si la variable a déjà été assignée
    bool val;       /// La valeur assignée. a ne pas prendre en compte si assigned==false.
};

bool operator<(int const a, Variable const& b); /** Ok, un peu overkill mais c'était sympa de ne pas se poser la question en codant **/
bool operator<(Variable const &a, int const b); /** Tout ceci sert à avoir un ordre arbitraire sur les variables comme décrit dans le sujet **/
bool operator<(Variable const &a, Variable const& b); /** En particulier pour ordonner les seaux. **/
bool operator>(int const a, Variable const& b);
bool operator>(Variable const &a, int const b);
bool operator>(Variable const &a, Variable const& b);
bool operator<=(int const a, Variable const& b);
bool operator<=(Variable const &a, int const b);
bool operator<=(Variable const &a, Variable const& b);
bool operator>=(int const a, Variable const& b);
bool operator>=(Variable const &a, int const b);
bool operator>=(Variable const &a, Variable const& b);
bool operator==(Variable const &a, Variable const& b);
bool operator==(int const a, Variable const& b);
bool operator==(Variable const &a, int const b);
bool operator!=(Variable const &a, Variable const& b);
bool operator!=(int const a, Variable const& b);
bool operator!=(Variable const &a, int const b);
#endif // VARIABLE_H
