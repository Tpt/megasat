#ifndef TERME_H
#define TERME_H

#include<string>
#include<vector>

class Terme
{
public:
    Terme();
    virtual ~Terme();
    bool isVariable() const;
    bool isFonction() const;
    std::string getSymbole() const;

private:
    std::vector<Terme*> parametres;
    std::string symbole;
    int variable;
};

#endif // TERME_H
