#ifndef CONNECTEURS_H_INCLUDED
#define CONNECTEURS_H_INCLUDED

#include<string>
#include "MessageException.h"

class FormuleTseitin
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
    FormuleTseitin(FormuleTypeSimple type_, std::string name_);
    FormuleTseitin(FormuleTypeSimple type_, FormuleTseitin* op);
    FormuleTseitin(FormuleTypeSimple type_, FormuleTseitin* opG, FormuleTseitin* opD);
    ~FormuleTseitin(); //Ne détruit pas récursivement. Pour ce faire, il faut utiliser la méthode free()
    std::string getName() const;
    int getArite() const __attribute__((pure));
    FormuleTseitin::FormuleTypeSimple getType() const __attribute__((pure));
    FormuleTseitin getOperandeG() const;
    FormuleTseitin getOperandeD() const;
    FormuleTseitin getOperande() const;
    FormuleTseitin* getOperandeGPointeur() const;
    FormuleTseitin* getOperandeDPointeur() const;
    FormuleTseitin* getOperandePointeur() const;
    std::string toStringType() const;
    std::string toStringPrefix() const;
    std::string toString() const;
    void print() const;
    void free();

private:
    int ariteDuType(const FormuleTseitin::FormuleTypeSimple& type_) const __attribute__((pure));

    FormuleTseitin* operandeG;
    FormuleTseitin* operandeD;
    FormuleTypeSimple type;
    std::string name;
};

class FormuleTseitinError : public MessageException
{
public:
    FormuleTseitinError(std::string message) noexcept : MessageException(message) {};
};


#endif // CONNECTEURS_H_INCLUDED
