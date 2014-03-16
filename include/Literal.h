#ifndef LITERAL_H
#define LITERAL_H

#include<cmath>
#include "Variable.h"

class Literal
{
public:
    Literal(Variable* var_, bool polarite_);
    Literal& operator=(const Literal& other);
    int getId() const;
    int getAbsId() const;
    bool isAssigne() const;
    bool getVal() const;
    bool getPolarite() const;
    Variable* getVar() const;
    void setVal(bool e);
    void print() const;
    ResultatEvaluation eval() const;

private:
    Variable* var; /// Le pointeur vers la variable correspondante.
    bool polarite; /// La polarité : si polarite==true, le literal vaut x sinon c'est non(x).
};

#endif // LITERAL_H
