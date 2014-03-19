#ifndef CONNECTEURS_H_INCLUDED
#define CONNECTEURS_H_INCLUDED

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
        NON,
        ET,
        OU,
        IMPLIQUE,
        XOR,
    };
    FormuleTseitinSimple();
    FormuleTseitinSimple(const FormuleTseitinSimple& F);///Obligatoire pour pouvoir utiliser un attribut pointeur
    FormuleTseitinSimple& operator=(const FormuleTseitinSimple& F);///Idem
    FormuleTseitinSimple(FormuleTypeSimple type_, std::string name_);
    FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple op);
    FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple* op);
    FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple opG, FormuleTseitinSimple opD);
    FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple* opG, FormuleTseitinSimple* opD);
    ~FormuleTseitinSimple();
    FormuleTseitinSimple transformationDeMorgan() const;
    std::string getName() const;
    int getArite() const;
    FormuleTseitinSimple::FormuleTypeSimple getType() const;
    FormuleTseitinSimple getOperandeG() const;
    FormuleTseitinSimple getOperandeD() const;
    FormuleTseitinSimple getOperande() const;
    FormuleTseitinSimple* getPOperandeG() const;
    FormuleTseitinSimple* getPOperandeD() const;
    FormuleTseitinSimple* getPOperande() const;
    std::string toStringType() const;
    std::string toStringPrefix() const;
    std::string toString() const;

private:
    int ariteDuType(const FormuleTseitinSimple::FormuleTypeSimple& type_) const;
    FormuleTseitinSimple descendreNon() const;
    FormuleTseitinSimple distribuerOu() const;
    FormuleTseitinSimple eliminerXor() const;
    FormuleTseitinSimple eliminerImplique() const

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


#endif // CONNECTEURS_H_INCLUDED
