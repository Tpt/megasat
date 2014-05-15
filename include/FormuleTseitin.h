#ifndef CONNECTEURS_H_INCLUDED
#define CONNECTEURS_H_INCLUDED

#include<string>
#include "MessageException.h"
#include "Terme.h"

template<typename T> class FormuleTseitin
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
    }; //l'état par défaut d'une FormuleTseitin est type = VARIABLE avec name = "". C'est nottament le cas si une erreur arrive.
    FormuleTseitin();
    FormuleTseitin(const FormuleTseitin& F);///Obligatoire pour pouvoir utiliser un attribut pointeur
    FormuleTseitin& operator=(const FormuleTseitin& F);///Idem
    FormuleTseitin(FormuleTypeSimple type_, T name_);
    FormuleTseitin(FormuleTypeSimple type_, FormuleTseitin* op);
    FormuleTseitin(FormuleTypeSimple type_, FormuleTseitin* opG, FormuleTseitin* opD);
    T getName() const __attribute__((pure));
    int getArite() const __attribute__((pure));
    FormuleTseitin::FormuleTypeSimple getType() const __attribute__((pure));
    FormuleTseitin<T> getOperandeG() const;
    FormuleTseitin<T> getOperandeD() const;
    FormuleTseitin<T> getOperande() const;
    std::string toStringPrefix() const;
    std::string toString() const;
    void print() const;
    void free();

private:
    int ariteDuType(const FormuleTseitin::FormuleTypeSimple& type_) const __attribute__((pure));

    FormuleTseitin* operandeG;
    FormuleTseitin* operandeD;
    FormuleTypeSimple type;
    T name;
};

class FormuleTseitinError : public MessageException
{
public:
    FormuleTseitinError(std::string message) noexcept : MessageException(message) {};
};

#include "../src/FormuleTseitin.cpp"

#endif // CONNECTEURS_H_INCLUDED
