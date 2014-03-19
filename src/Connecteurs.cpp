#include "../include/Connecteurs.h"
#include<iostream>
#include<sstream>

using namespace std;

string toString_(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}

int FormuleTseitinSimple::ariteDuType(const FormuleTseitinSimple::FormuleTypeSimple& type_) const
{
    switch(type_)
    {
    case FormuleTseitinSimple::VARIABLE :
        return 0;
    case FormuleTseitinSimple::NON :
        return 1;
    case FormuleTseitinSimple::OU :
    case FormuleTseitinSimple::ET :
    case FormuleTseitinSimple::IMPLIQUE :
    case FormuleTseitinSimple::XOR :
    default :
        return 2;
    }
}

FormuleTseitinSimple::FormuleTseitinSimple() :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitinSimple::VARIABLE), name("")
{}

FormuleTseitinSimple::FormuleTseitinSimple(const FormuleTseitinSimple& F) :
operandeG(F.operandeG), operandeD(F.operandeD), type(F.type), name(F.name)
{}

FormuleTseitinSimple& FormuleTseitinSimple::operator= (const FormuleTseitinSimple& other)
{
    FormuleTseitinSimple Temp(other);

    swap(Temp.operandeG, this->operandeG);
    swap(Temp.operandeD, this->operandeD);
    swap(Temp.type, this->type);
    swap(Temp.name, this->name);

    return *this;
}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, std::string name_) :
    operandeG(nullptr), operandeD(nullptr), type(FormuleTseitinSimple::VARIABLE), name("")
{
    if(type_ != FormuleTseitinSimple::VARIABLE)
        throw FormuleTseitinSimpleError( "Le type devrait être une variable !");

    name=name_;
}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple* op) :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitinSimple::VARIABLE), name("")
{
    if(ariteDuType(type_) != 1)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 1 ! (bis)");


    type = type_;
    operandeG = op;

}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple* opG, FormuleTseitinSimple* opD) :
operandeG(nullptr), operandeD(nullptr), type(FormuleTseitinSimple::VARIABLE), name("")
{
    if(ariteDuType(type_) != 2)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 2 !");

    type = type_;
    operandeG = opG;
    operandeD = opD;

}

FormuleTseitinSimple::~FormuleTseitinSimple()
{

}

string FormuleTseitinSimple::getName() const
{
    return name;
}

FormuleTseitinSimple* FormuleTseitinSimple::getPOperandeG() const
{
    if(getArite()!=2)
        throw FormuleTseitinSimpleError("Le type devrait avoir une arité 2 !");
    return operandeG;
}

FormuleTseitinSimple* FormuleTseitinSimple::getPOperandeD() const
{
    if(getArite()!=2)
        throw FormuleTseitinSimpleError("Le type devrait avoir une arité 2 !");
    return operandeD;
}

FormuleTseitinSimple* FormuleTseitinSimple::getPOperande() const
{
    if(getArite()!=1)
        throw FormuleTseitinSimpleError("Le type devrait avoir une arité 1 ! (ter)");
    return operandeG;
}

FormuleTseitinSimple FormuleTseitinSimple::getOperandeG() const
{
    if(getArite()!=2)
        throw FormuleTseitinSimpleError("Le type devrait avoir une arité 2 !");
    return *operandeG;
}

FormuleTseitinSimple FormuleTseitinSimple::getOperandeD() const
{
    if(getArite()!=2)
        throw FormuleTseitinSimpleError("Le type devrait avoir une arité 2 !");
    return *operandeD;
}

FormuleTseitinSimple FormuleTseitinSimple::getOperande() const
{
    if(getArite()!=1)
        throw FormuleTseitinSimpleError("Le type devrait avoir une arité 1 ! (quad)"+to_string(type)+name);
    return *operandeG;
}

int FormuleTseitinSimple::getArite() const
{
    return ariteDuType(type);
}

FormuleTseitinSimple::FormuleTypeSimple FormuleTseitinSimple::getType() const
{
    return type;
}

string FormuleTseitinSimple::toStringPrefix() const
{
    //cout<<"!"<<toString_(getType())<<endl;

    switch(type)
    {
        case FormuleTseitinSimple::VARIABLE :
            //cout<<"#"<<name<<endl;
            return name;
        case FormuleTseitinSimple::NON :
            //cout<<"~"<<endl;
            return "~ " + operandeG->toStringPrefix();
        case FormuleTseitinSimple::OU :
            //cout<<"ou"<<endl;
            return "ou " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitinSimple::ET :
            //cout<<"et"<<endl;
            return "et " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitinSimple::IMPLIQUE :
            //cout<<"imp"<<endl;
            return "=> " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        case FormuleTseitinSimple::XOR :
            //cout<<"xor"<<endl;
            return "xor " + operandeG->toStringPrefix() + " " + operandeD->toStringPrefix();
        default :
            //cout<<"FAIL ! "<<endl;
            return "P'tet ben, j'en sais rien...";
    }
}

string FormuleTseitinSimple::toStringType() const
{
    switch(type)
    {
        case FormuleTseitinSimple::VARIABLE :
            return "var";
        case FormuleTseitinSimple::NON :
            return "~";
        case FormuleTseitinSimple::OU :
            return "ou ";
        case FormuleTseitinSimple::ET :
            return "et";
        case FormuleTseitinSimple::IMPLIQUE :
            return "=>";
        case FormuleTseitinSimple::XOR :
            return "xor";
        default :
            return "P'tet ben, j'en sais rien...";
    }
}

string FormuleTseitinSimple::toString() const
{
    switch(type)
    {
        case FormuleTseitinSimple::VARIABLE :
            return name;
        case FormuleTseitinSimple::NON :
            return "~" + operandeG->toString();
        case FormuleTseitinSimple::OU :
            return "(" + operandeG->toString() + " \\/ " + operandeD->toString() + ")";
        case FormuleTseitinSimple::ET :
            return "(" + operandeG->toString() + " /\\ " + operandeD->toString() + ")";
        case FormuleTseitinSimple::IMPLIQUE :
            return "(" + operandeG->toString() + " => " + operandeD->toString() + ")";
        case FormuleTseitinSimple::XOR :
            return "(" + operandeG->toString() + " xor " + operandeD->toString() + ")";
        default :
            return "P'tet ben, j'en sais rien...";
    }
}
