#ifndef VARIABLE_H
#define VARIABLE_H

#include<vector>
#include "ResultatEvaluation.h"

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
    int id;         /// Le numéro de la variable compté à partir de 1
    bool assigned;  /// Si la variable a déjà été assignée
    bool val;       /// La valeur assignée. a ne pas prendre en compte si assigned==false.
};

#endif // VARIABLE_H
