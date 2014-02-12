#ifndef CLITERAL_H
#define CLITERAL_H

#include<cmath>
#include"CVariable.h"

class CLiteral
{
    public:
    CLiteral();
    CLiteral(CVariable* a, bool pol);
    virtual ~CLiteral();
    CLiteral(const CLiteral& other);
    CLiteral& operator=(const CLiteral& other);
    int getId() const;
    int getAbsId() const;
    bool less(CLiteral const& b) const;
    bool eless(CLiteral const& b) const;
    bool isAssigned() const;
    bool getVal() const;
    bool getPolarite() const;
    CVariable* getVar() const;
    void setVal(bool e);
    void print() const;

    private:
    CVariable* var;     /// Le pointeur vers la variable correspondante.
    bool polarite;      /// La polarité : si polarite==true, le literal vaut x sinon c'est non(x).
};

bool operator<(int const a, CLiteral const& b); /** Toujours aussi overkill **/
bool operator<(CLiteral const& a, int const b);
bool operator<(CLiteral const& a, CLiteral const& b);
bool operator>(int const a, CLiteral const& b);
bool operator>(CLiteral const& a, int const b);
bool operator>(CLiteral const& a, CLiteral const& b);
bool operator<=(int const a, CLiteral const& b);
bool operator<=(CLiteral const& a, int const b);
bool operator<=(CLiteral const& a, CLiteral const& b);
bool operator>=(int const a, CLiteral const& b);
bool operator>=(CLiteral const& a, int const b);
bool operator>=(CLiteral const& a, CLiteral const& b);
bool operator==(int const a, CLiteral const& b);
bool operator==(CLiteral const& a, int const b);
bool operator==(CLiteral const& a, CLiteral const& b);
bool operator!=(int const a, CLiteral const& b);
bool operator!=(CLiteral const& a, int const b);
bool operator!=(CLiteral const& a, CLiteral const& b);

#endif // CLITERAL_H
