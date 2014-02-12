#ifndef CVARIABLE_H
#define CVARIABLE_H

#include<vector>

class CVariable
{
    public:
    CVariable();
    CVariable(int id_e);
    ~CVariable();
    CVariable(const CVariable& other);
    int getId() const;
    bool less(CVariable const& b) const;
    bool eless(CVariable const& b) const;
    bool isAssigned() const;
    bool getVal() const;
    void setVal(bool e);

    private:
    int id;         /// Le numéro de la variable
    bool assigned;  /// Si la variable a déjà été assignée
    bool val;       /// La valeur assignée. a ne pas prendre en compte si assigned==false.
};

bool operator<(int const a, CVariable const& b); /** Ok, un peu overkill mais c'était sympa de ne pas se poser la question en codant **/
bool operator<(CVariable const &a, int const b); /** Tout ceci sert à avoir un ordre arbitraire sur les variables comme dévrit dans le sujet **/
bool operator<(CVariable const &a, CVariable const& b); /** En particulier pour ordonner les seaux. **/
bool operator>(int const a, CVariable const& b);
bool operator>(CVariable const &a, int const b);
bool operator>(CVariable const &a, CVariable const& b);
bool operator<=(int const a, CVariable const& b);
bool operator<=(CVariable const &a, int const b);
bool operator<=(CVariable const &a, CVariable const& b);
bool operator>=(int const a, CVariable const& b);
bool operator>=(CVariable const &a, int const b);
bool operator>=(CVariable const &a, CVariable const& b);
bool operator==(CVariable const &a, CVariable const& b);
bool operator==(int const a, CVariable const& b);
bool operator==(CVariable const &a, int const b);
bool operator!=(CVariable const &a, CVariable const& b);
bool operator!=(int const a, CVariable const& b);
bool operator!=(CVariable const &a, int const b);
#endif // CVARIABLE_H
