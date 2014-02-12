#ifndef LITERAL_H
#define LITERAL_H

#include<cmath>
#include"Variable.h"

class Literal
{
    public:
    Literal();
    Literal(Variable* a, bool pol);
    virtual ~Literal();
    Literal(const Literal& other);
    Literal& operator=(const Literal& other);
    int getId() const;
    int getAbsId() const;
    bool less(Literal const& b) const;
    bool eless(Literal const& b) const;
    bool isAssigned() const;
    bool getVal() const;
    bool getPolarite() const;
    Variable* getVar() const;
    void setVal(bool e);
    void print() const;

    private:
    Variable* var;     /// Le pointeur vers la variable correspondante.
    bool polarite;      /// La polarité : si polarite==true, le literal vaut x sinon c'est non(x).
};

bool operator<(int const a, Literal const& b); /** Toujours aussi overkill **/
bool operator<(Literal const& a, int const b);
bool operator<(Literal const& a, Literal const& b);
bool operator>(int const a, Literal const& b);
bool operator>(Literal const& a, int const b);
bool operator>(Literal const& a, Literal const& b);
bool operator<=(int const a, Literal const& b);
bool operator<=(Literal const& a, int const b);
bool operator<=(Literal const& a, Literal const& b);
bool operator>=(int const a, Literal const& b);
bool operator>=(Literal const& a, int const b);
bool operator>=(Literal const& a, Literal const& b);
bool operator==(int const a, Literal const& b);
bool operator==(Literal const& a, int const b);
bool operator==(Literal const& a, Literal const& b);
bool operator!=(int const a, Literal const& b);
bool operator!=(Literal const& a, int const b);
bool operator!=(Literal const& a, Literal const& b);

#endif // LITERAL_H
