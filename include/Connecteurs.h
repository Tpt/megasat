#ifndef CONNECTEURS_H_INCLUDED
#define CONNECTEURS_H_INCLUDED

#include<string>
#include "MessageException.h"

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
        XOR
    }; //l'état par défaut d'une FormuleTseitinSimple est type = VARIABLE avec name = "". C'est nottament le cas si une erreur arrive.
    FormuleTseitinSimple();
    FormuleTseitinSimple(const FormuleTseitinSimple& F);///Obligatoire pour pouvoir utiliser un attribut pointeur
    FormuleTseitinSimple& operator=(const FormuleTseitinSimple& F);///Idem
    FormuleTseitinSimple(FormuleTypeSimple type_, std::string name_);
    FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple* op);
    FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple* opG, FormuleTseitinSimple* opD);
    ~FormuleTseitinSimple();
    std::string getName() const;
    int getArite() const;
    FormuleTseitinSimple::FormuleTypeSimple getType() const;
    FormuleTseitinSimple getOperandeG() const;
    FormuleTseitinSimple getOperandeD() const;
    FormuleTseitinSimple getOperande() const;
    FormuleTseitinSimple* getOperandeGPointeur() const;
    FormuleTseitinSimple* getOperandeDPointeur() const;
    FormuleTseitinSimple* getOperandePointeur() const;
    std::string toStringType() const;
    std::string toStringPrefix() const;
    std::string toString() const;
    void print() const;

private:
    int ariteDuType(const FormuleTseitinSimple::FormuleTypeSimple& type_) const;

    FormuleTseitinSimple* operandeG;
    FormuleTseitinSimple* operandeD;
    FormuleTypeSimple type;
    std::string name;
};

class FormuleTseitinSimpleError : public MessageException
{
public:
    FormuleTseitinSimpleError(std::string message) noexcept : MessageException(message) {};
};


#endif // CONNECTEURS_H_INCLUDED
