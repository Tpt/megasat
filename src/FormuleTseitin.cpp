#include "../include/FormuleTseitin.h"
#include<iostream>
#include<sstream>

using namespace std;

template<typename T> int FormuleTseitin<T>::ariteDuType(const FormuleTseitin<T>::FormuleTypeSimple& type_) const
{
    switch(type_)
    {
    case FormuleTseitin<T>::VARIABLE :
        return 0;
    case FormuleTseitin<T>::NON :
        return 1;
    case FormuleTseitin<T>::OU :
    case FormuleTseitin<T>::ET :
    case FormuleTseitin<T>::IMPLIQUE :
    case FormuleTseitin<T>::XOR :
    default :
        return 2;
    }
}

template<typename T> FormuleTseitin<T>::FormuleTseitin() :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitin<T>::VARIABLE), name(T())
{}

template<typename T> FormuleTseitin<T>::FormuleTseitin(const FormuleTseitin<T>& F) :
operandeG(F.operandeG), operandeD(F.operandeD), type(F.type), name(F.name)
{}

template<typename T> FormuleTseitin<T>& FormuleTseitin<T>::operator= (const FormuleTseitin<T>& other)
{
    FormuleTseitin<T> Temp(other);

    swap(Temp.operandeG, this->operandeG);
    swap(Temp.operandeD, this->operandeD);
    swap(Temp.type, this->type);
    swap(Temp.name, this->name);

    return *this;
}

template<typename T> FormuleTseitin<T>::FormuleTseitin(FormuleTypeSimple type_, T name_) :
    operandeG(nullptr), operandeD(nullptr), type(FormuleTseitin<T>::VARIABLE), name(T())
{
    if(type_ != FormuleTseitin<T>::VARIABLE)
        throw FormuleTseitinError( "Le type devrait être une variable !");

    name=name_;
}

template<typename T> FormuleTseitin<T>::FormuleTseitin(FormuleTypeSimple type_, FormuleTseitin<T>* op) :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitin<T>::VARIABLE), name(T())
{
    if(ariteDuType(type_) != 1)
        throw FormuleTseitinError( "Le type devrait avoir une arité 1 ! (bis)");


    type = type_;
    operandeG = op;

}

template<typename T> FormuleTseitin<T>::FormuleTseitin(FormuleTypeSimple type_, FormuleTseitin<T>* opG, FormuleTseitin<T>* opD) :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitin<T>::VARIABLE), name(T())
{
    if(ariteDuType(type_) != 2)
        throw FormuleTseitinError( "Le type devrait avoir une arité 2 !");

    type = type_;
    operandeG = opG;
    operandeD = opD;

}

template<typename T> T FormuleTseitin<T>::getName() const
{
    return name;
}

template<typename T> FormuleTseitin<T> FormuleTseitin<T>::getOperandeG() const
{
    if(getArite()!=2)
        throw FormuleTseitinError("Le type devrait avoir une arité 2 !");
    return *operandeG;
}

template<typename T> FormuleTseitin<T> FormuleTseitin<T>::getOperandeD() const
{
    if(getArite()!=2)
        throw FormuleTseitinError("Le type devrait avoir une arité 2 !");
    return *operandeD;
}

template<typename T> FormuleTseitin<T> FormuleTseitin<T>::getOperande() const
{
    if(getArite() != 1)
        throw FormuleTseitinError("Le type devrait avoir une arité 1 ! (quad)" + to_string(type));
    return *operandeG;
}

template<typename T> int FormuleTseitin<T>::getArite() const
{
    return ariteDuType(type);
}

template<typename T> typename FormuleTseitin<T>::FormuleTypeSimple FormuleTseitin<T>::getType() const
{
    return type;
}

template<typename T> string FormuleTseitin<T>::toStringPrefix() const
{

    switch(type)
    {
        case FormuleTseitin<T>::VARIABLE :
            return name;
        case FormuleTseitin<T>::NON :
            return "~ " + operandeG->toStringPrefix();
        case FormuleTseitin<T>::OU :
            return "ou " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitin<T>::ET :
            return "et " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitin<T>::IMPLIQUE :
            return "=> " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitin<T>::XOR :
            return "xor " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        default :
            return "P'tet ben, j'en sais rien...";
    }
}

template<typename T> string FormuleTseitin<T>::toStringType() const
{
    switch(type)
    {
        case FormuleTseitin<T>::VARIABLE :
            return "var";
        case FormuleTseitin<T>::NON :
            return "~";
        case FormuleTseitin<T>::OU :
            return "ou ";
        case FormuleTseitin<T>::ET :
            return "et";
        case FormuleTseitin<T>::IMPLIQUE :
            return "=>";
        case FormuleTseitin<T>::XOR :
            return "xor";
        default :
            return "P'tet ben, j'en sais rien...";
    }
}

template<typename T> string FormuleTseitin<T>::toString() const
{
    switch(type)
    {
        case FormuleTseitin<T>::VARIABLE :
            return "";
        case FormuleTseitin<T>::NON :
            return "~" + operandeG->toString();
        case FormuleTseitin<T>::OU :
            return "(" + operandeG->toString() + " \\/ " + operandeD->toString() + ")";
        case FormuleTseitin<T>::ET :
            return "(" + operandeG->toString() + " /\\ " + operandeD->toString() + ")";
        case FormuleTseitin<T>::IMPLIQUE :
            return "(" + operandeG->toString() + " => " + operandeD->toString() + ")";
        case FormuleTseitin<T>::XOR :
            return "(" + operandeG->toString() + " xor " + operandeD->toString() + ")";
        default :
            return "P'tet ben, j'en sais rien...";
    }
}

template<typename T> void FormuleTseitin<T>::print() const
{
    cout << toString() << endl;
}


template<typename T> void FormuleTseitin<T>::free()
{
    if(getArite() >= 1)
    {
        operandeG->free();
        delete operandeG;
    }
    if(getArite() >= 2)
    {
        operandeD->free();
        delete operandeD;
    }
}
