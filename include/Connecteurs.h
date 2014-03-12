#ifndef CONNECTEURS_H_INCLUDED
#define CONNECTEURS_H_INCLUDED

#include<string>

class FormuleTseitin
{
    public:
    enum FormuleType
    {
        VARIABLE,
        ET,
        OU,
        IMPLIQUE,
        XOR,
        NON, //Le C++11 autorise cette virgule !!!
    };
    FormuleTseitin(){};
    virtual ~FormuleTseitin() = 0;
    virtual FormuleTseitin* simplifier() = 0;
    virtual FormuleType getType() = 0;
};

class VariablePropositionnelle : public FormuleTseitin
{
public:
    VariablePropositionnelle(std::string name_) : name(name_){};
    virtual ~VariablePropositionnelle(){};
    virtual FormuleTseitin* simplifier();
    virtual FormuleType getType();
    std::string getName() const {return name;};

private:
    std::string name;
};

class ConnecteurBinaire : public FormuleTseitin
{
public:
    ConnecteurBinaire(FormuleTseitin* op1, FormuleTseitin* op2) : operandeG(*op1), operandeD(*op2){};
    virtual ~ConnecteurBinaire() = 0;
    virtual FormuleTseitin* simplifier() = 0;
    virtual FormuleType getType() = 0;
    FormuleTseitin* getOperandeG() const;
    FormuleTseitin* getOperandeD() const;

protected:
    FormuleTseitin& operandeG;
    FormuleTseitin& operandeD;
};

class Et : public ConnecteurBinaire
{
public:
    Et(FormuleTseitin* op1, FormuleTseitin* op2) : ConnecteurBinaire(op1, op2){};
    virtual ~Et(){};
    virtual FormuleTseitin* simplifier();
    virtual FormuleType getType();
};


class Ou : public ConnecteurBinaire
{
public:
    Ou(FormuleTseitin* op1, FormuleTseitin* op2) : ConnecteurBinaire(op1, op2){};
    virtual ~Ou(){};
    virtual FormuleTseitin* simplifier();
    virtual FormuleType getType();
};

class Xor : public ConnecteurBinaire
{
public:
    Xor(FormuleTseitin* op1, FormuleTseitin* op2) : ConnecteurBinaire(op1, op2){};
    virtual ~Xor(){};
    virtual FormuleTseitin* simplifier();
    virtual FormuleType getType();
};

class Implique : public ConnecteurBinaire
{
public:
    Implique(FormuleTseitin* op1, FormuleTseitin* op2) : ConnecteurBinaire(op1, op2){};
    virtual ~Implique(){};
    virtual FormuleTseitin* simplifier();
    virtual FormuleType getType();
};

class ConnecteurUnaire : public FormuleTseitin
{
public:
    ConnecteurUnaire(FormuleTseitin* op) : operande(*op){};
    virtual ~ConnecteurUnaire() = 0;
    virtual FormuleTseitin* simplifier() = 0;
    virtual FormuleType getType() = 0;
    FormuleTseitin* getOperande() const;

protected:
    FormuleTseitin& operande;
};

class Non : public ConnecteurUnaire
{
public:
    Non(FormuleTseitin* op) : ConnecteurUnaire(op){};
    virtual ~Non(){};
    virtual FormuleTseitin* simplifier();
    virtual FormuleType getType();
};

#endif // CONNECTEURS_H_INCLUDED
