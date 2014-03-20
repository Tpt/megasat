#include "../include/FormuleTseitin.h"
#include<iostream>
#include<sstream>

using namespace std;

int FormuleTseitin::ariteDuType(const FormuleTseitin::FormuleTypeSimple& type_) const
{
    switch(type_)
    {
    case FormuleTseitin::VARIABLE :
        return 0;
    case FormuleTseitin::NON :
        return 1;
    case FormuleTseitin::OU :
    case FormuleTseitin::ET :
    case FormuleTseitin::IMPLIQUE :
    case FormuleTseitin::XOR :
    default :
        return 2;
    }
}

FormuleTseitin::FormuleTseitin() :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitin::VARIABLE), name("")
{}

FormuleTseitin::FormuleTseitin(const FormuleTseitin& F) :
operandeG(F.operandeG), operandeD(F.operandeD), type(F.type), name(F.name)
{}

FormuleTseitin& FormuleTseitin::operator= (const FormuleTseitin& other)
{
    FormuleTseitin Temp(other);

    swap(Temp.operandeG, this->operandeG);
    swap(Temp.operandeD, this->operandeD);
    swap(Temp.type, this->type);
    swap(Temp.name, this->name);

    return *this;
}

FormuleTseitin::FormuleTseitin(FormuleTypeSimple type_, std::string name_) :
    operandeG(nullptr), operandeD(nullptr), type(FormuleTseitin::VARIABLE), name("")
{
    if(type_ != FormuleTseitin::VARIABLE)
        throw FormuleTseitinError( "Le type devrait être une variable !");

    name=name_;
}

FormuleTseitin::FormuleTseitin(FormuleTypeSimple type_, FormuleTseitin* op) :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitin::VARIABLE), name("")
{
    if(ariteDuType(type_) != 1)
        throw FormuleTseitinError( "Le type devrait avoir une arité 1 ! (bis)");


    type = type_;
    operandeG = op;

}

FormuleTseitin::FormuleTseitin(FormuleTypeSimple type_, FormuleTseitin* opG, FormuleTseitin* opD) :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitin::VARIABLE), name("")
{
    if(ariteDuType(type_) != 2)
        throw FormuleTseitinError( "Le type devrait avoir une arité 2 !");

    type = type_;
    operandeG = opG;
    operandeD = opD;

}

FormuleTseitin::~FormuleTseitin()
{

}

string FormuleTseitin::getName() const
{
    return name;
}

FormuleTseitin* FormuleTseitin::getOperandeGPointeur() const
{
    if(getArite()!=2)
        throw FormuleTseitinError("Le type devrait avoir une arité 2 !");
    return operandeG;
}

FormuleTseitin* FormuleTseitin::getOperandeDPointeur() const
{
    if(getArite()!=2)
        throw FormuleTseitinError("Le type devrait avoir une arité 2 !");
    return operandeD;
}

FormuleTseitin* FormuleTseitin::getOperandePointeur() const
{
    if(getArite()!=1)
        throw FormuleTseitinError("Le type devrait avoir une arité 1 ! (ter)");
    return operandeG;
}

FormuleTseitin FormuleTseitin::getOperandeG() const
{
    if(getArite()!=2)
        throw FormuleTseitinError("Le type devrait avoir une arité 2 !");
    return *operandeG;
}

FormuleTseitin FormuleTseitin::getOperandeD() const
{
    if(getArite()!=2)
        throw FormuleTseitinError("Le type devrait avoir une arité 2 !");
    return *operandeD;
}

FormuleTseitin FormuleTseitin::getOperande() const
{
    if(getArite()!=1)
        throw FormuleTseitinError("Le type devrait avoir une arité 1 ! (quad)"+to_string(type)+name);
    return *operandeG;
}

int FormuleTseitin::getArite() const
{
    return ariteDuType(type);
}

FormuleTseitin::FormuleTypeSimple FormuleTseitin::getType() const
{
    return type;
}

string FormuleTseitin::toStringPrefix() const
{

    switch(type)
    {
        case FormuleTseitin::VARIABLE :
            //cout<<"#"<<name<<endl;
            return name;
        case FormuleTseitin::NON :
            //cout<<"~"<<endl;
            return "~ " + operandeG->toStringPrefix();
        case FormuleTseitin::OU :
            //cout<<"ou"<<endl;
            return "ou " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitin::ET :
            //cout<<"et"<<endl;
            return "et " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitin::IMPLIQUE :
            //cout<<"imp"<<endl;
            return "=> " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitin::XOR :
            //cout<<"xor"<<endl;
            return "xor " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        default :
            //cout<<"FAIL ! "<<endl;
            return "P'tet ben, j'en sais rien...";
    }
}

string FormuleTseitin::toStringType() const
{
    switch(type)
    {
        case FormuleTseitin::VARIABLE :
            return "var";
        case FormuleTseitin::NON :
            return "~";
        case FormuleTseitin::OU :
            return "ou ";
        case FormuleTseitin::ET :
            return "et";
        case FormuleTseitin::IMPLIQUE :
            return "=>";
        case FormuleTseitin::XOR :
            return "xor";
        default :
            return "P'tet ben, j'en sais rien...";
    }
}

string FormuleTseitin::toString() const
{
    switch(type)
    {
        case FormuleTseitin::VARIABLE :
            return name;
        case FormuleTseitin::NON :
            return "~" + operandeG->toString();
        case FormuleTseitin::OU :
            return "(" + operandeG->toString() + " \\/ " + operandeD->toString() + ")";
        case FormuleTseitin::ET :
            return "(" + operandeG->toString() + " /\\ " + operandeD->toString() + ")";
        case FormuleTseitin::IMPLIQUE :
            return "(" + operandeG->toString() + " => " + operandeD->toString() + ")";
        case FormuleTseitin::XOR :
            return "(" + operandeG->toString() + " xor " + operandeD->toString() + ")";
        default :
            return "P'tet ben, j'en sais rien...";
    }
}

void FormuleTseitin::print() const
{
    cout<<toString()<<endl;
}
