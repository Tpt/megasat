#ifndef LITERAL_H
#define LITERAL_H

#include<cmath>
#include "Variable.h"

class Literal
{
public:
    Literal(Variable* var_, bool polarite_);
    Literal& operator=(const Literal& other);
    int getId() const __attribute__((pure));
    int getAbsId() const __attribute__((pure));
    bool isAssigne() const __attribute__((pure));
    bool getVal() const __attribute__((pure));
    bool getPolarite() const __attribute__((pure));
    Variable* getVar() const __attribute__((pure));
    void setVal(bool e);
    void print() const;
    ResultatEvaluation eval() const __attribute__((pure));

private:
    Variable* var; /// Le pointeur vers la variable correspondante.
    bool polarite; /// La polarité : si polarite==true, le literal vaut x sinon c'est non(x).
};

#endif // LITERAL_H
