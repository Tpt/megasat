#ifndef CONNECTEURS_H_INCLUDED
#define CONNECTEURS_H_INCLUDED
#define cosnt const

#include<string>

/***

Si l'affectation echoue, on a un type variable de nom vide et seulement dans ce cas.

***/

class FormuleTseitinSimple
{
public:
    enum FormuleTypeSimple
    {
        VARIABLE,
        ET,
        OU,
        IMPLIQUE,
        XOR,
        NON, //Le C++11 autorise cette virgule !!!
    };
    FormuleTseitinSimple();
    FormuleTseitinSimple(const FormuleTseitinSimple& F);///Obligatoire pour pouvoir utiliser un attribut pointeur
    FormuleTseitinSimple& operator=(const FormuleTseitinSimple& F);///Idem
    FormuleTseitinSimple(FormuleTypeSimple type_, std::string name_);
    FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple op);
    FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple opG, FormuleTseitinSimple opD);
    ~FormuleTseitinSimple();
    FormuleTseitinSimple normaliser() const;
    std::string getName() const;
    std::string toString() const;

private:
    FormuleTseitinSimple getOperandeG() const;
    FormuleTseitinSimple getOperandeD() const;
    FormuleTseitinSimple getOperande() const;
    int getArite() const;
    FormuleTseitinSimple::FormuleTypeSimple getType() const;
    int ariteDuType(const FormuleTseitinSimple::FormuleTypeSimple& type_) const;

    FormuleTseitinSimple descendreNon() const;
    FormuleTseitinSimple distribuerOu() const;
    FormuleTseitinSimple eliminerXor() const;
    FormuleTseitinSimple eliminerImplique() const;

    FormuleTseitinSimple* operandeG;
    FormuleTseitinSimple* operandeD;
    FormuleTypeSimple type;
    std::string name;
};

class FormuleTseitinSimpleError: public std::exception
{
public :
FormuleTseitinSimpleError(std::string message) noexcept :
    msg(message) {};
    ~FormuleTseitinSimpleError() noexcept {};
    std::string getMessage() const
    {
        return msg;
    };
private :
    std::string msg;
};

/*
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
    virtual FormuleTseitin& simplifier() = 0;
    virtual FormuleType getType() = 0;
};

class VariablePropositionnelle : public FormuleTseitin
{
public:
    VariablePropositionnelle(std::string name_) : name(name_){};
    virtual ~VariablePropositionnelle(){};
    virtual FormuleTseitin& simplifier();
    virtual FormuleType getType();
    std::string getName() const {return name;};

private:
    std::string name;
};

class ConnecteurBinaire : public FormuleTseitin
{
public:
    ConnecteurBinaire(FormuleTseitin& op1, FormuleTseitin& op2) : operandeG(op1), operandeD(op2){};
    virtual ~ConnecteurBinaire() = 0;
    virtual FormuleTseitin& simplifier() = 0;
    virtual FormuleType getType() = 0;
    FormuleTseitin& getOperandeG() const;
    FormuleTseitin& getOperandeD() const;

protected:
    FormuleTseitin& operandeG;
    FormuleTseitin& operandeD;
};

class Et : public ConnecteurBinaire
{
public:
    Et(FormuleTseitin& op1, FormuleTseitin& op2) : ConnecteurBinaire(op1, op2){};
    virtual ~Et(){};
    virtual FormuleTseitin& simplifier();
    virtual FormuleType getType();
};


class Ou : public ConnecteurBinaire
{
public:
    Ou(FormuleTseitin& op1, FormuleTseitin& op2) : ConnecteurBinaire(op1, op2){};
    virtual ~Ou(){};
    virtual FormuleTseitin& simplifier();
    virtual FormuleType getType();
};

class Xor : public ConnecteurBinaire
{
public:
    Xor(FormuleTseitin& op1, FormuleTseitin& op2) : ConnecteurBinaire(op1, op2){};
    virtual ~Xor(){};
    virtual FormuleTseitin& simplifier();
    virtual FormuleType getType();
};

class Implique : public ConnecteurBinaire
{
public:
    Implique(FormuleTseitin& op1, FormuleTseitin& op2) : ConnecteurBinaire(op1, op2){};
    virtual ~Implique(){};
    virtual FormuleTseitin& simplifier();
    virtual FormuleType getType();
};

class ConnecteurUnaire : public FormuleTseitin
{
public:
    ConnecteurUnaire(FormuleTseitin& op) : operande(op){};
    virtual ~ConnecteurUnaire() = 0;
    virtual FormuleTseitin& simplifier() = 0;
    virtual FormuleType getType() = 0;
    FormuleTseitin& getOperande() const;

protected:
    FormuleTseitin& operande;
};

class Non : public ConnecteurUnaire
{
public:
    Non(FormuleTseitin& op) : ConnecteurUnaire(op){};
    virtual ~Non(){};
    virtual FormuleTseitin& simplifier();
    virtual FormuleType getType();
};*/

#endif // CONNECTEURS_H_INCLUDED
