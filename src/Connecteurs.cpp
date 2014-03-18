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
    operandeG(nullptr), operandeD(nullptr), type(FormuleTseitinSimple::VARIABLE), name(name_)
{
    if(type_ != FormuleTseitinSimple::VARIABLE)
        throw FormuleTseitinSimpleError( "Le type devrait être une variable !");
}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple op) :
    operandeG(nullptr), operandeD(nullptr), type(type_), name("")
{
    if(ariteDuType(type_) != 1)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 1 !");

    operandeG = new FormuleTseitinSimple(op);
}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple* op) :
operandeG(nullptr), operandeD(nullptr), type(type_), name("")
{
    if(ariteDuType(type_) != 1)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 1 ! (bis)");


    operandeG=op;

}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple opG, FormuleTseitinSimple opD) :
    operandeG(nullptr), operandeD(nullptr), type(type_), name("")
{
    if(ariteDuType(type_) != 2)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 2 !");

    operandeG = new FormuleTseitinSimple(opG);
    operandeD = new FormuleTseitinSimple(opD);
}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple* opG, FormuleTseitinSimple* opD) :
operandeG(nullptr), operandeD(nullptr), type(type_), name("")
{
    if(ariteDuType(type_) != 2)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 2 !");


    operandeG=opG;
    operandeD=opD;

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

FormuleTseitinSimple FormuleTseitinSimple::distribuerOu() const
{
    if(getType()==FormuleTseitinSimple::OU)
    {
        if(getOperandeD().getType()==FormuleTseitinSimple::ET && getOperandeG().getType()==FormuleTseitinSimple::ET)
        {
            return  FormuleTseitinSimple(
                        FormuleTseitinSimple::ET,
                        FormuleTseitinSimple(
                            FormuleTseitinSimple::ET,
                            FormuleTseitinSimple(
                                FormuleTseitinSimple::OU,
                                getOperandeG().getOperandeG(),
                                getOperandeD().getOperandeG()
                            ),
                            FormuleTseitinSimple(
                                FormuleTseitinSimple::OU,
                                getOperandeG().getOperandeG(),
                                getOperandeD().getOperandeD()
                            )
                        ),
                        FormuleTseitinSimple(
                            FormuleTseitinSimple::ET,
                            FormuleTseitinSimple(
                                FormuleTseitinSimple::OU,
                                getOperandeG().getOperandeD(),
                                getOperandeD().getOperandeG()
                            ),
                            FormuleTseitinSimple(
                                FormuleTseitinSimple::OU,
                                getOperandeG().getOperandeD(),
                                getOperandeD().getOperandeD()
                            )
                        )
                    ).distribuerOu();///The longest instruction ever !!!
        }
        else if(getOperandeG().getType()==FormuleTseitinSimple::ET)
        {
            return  FormuleTseitinSimple(
                        FormuleTseitinSimple::ET,
                        FormuleTseitinSimple(
                            FormuleTseitinSimple::OU,
                            getOperandeG().getOperandeG(),
                            getOperandeD()
                        ),
                        FormuleTseitinSimple(
                            FormuleTseitinSimple::OU,
                            getOperandeG().getOperandeD(),
                            getOperandeD()
                        )
                    ).distribuerOu();
        }
        else if(getOperandeD().getType()==FormuleTseitinSimple::ET)
        {
            return  FormuleTseitinSimple(
                        FormuleTseitinSimple::ET,
                        FormuleTseitinSimple(
                            FormuleTseitinSimple::OU,
                            getOperandeD().getOperandeG(),
                            getOperandeG()
                        ),
                        FormuleTseitinSimple(
                            FormuleTseitinSimple::OU,
                            getOperandeD().getOperandeD(),
                            getOperandeG()
                        )
                    ).distribuerOu();
        }
    }
    else if(ariteDuType(getType())==2)
        return  FormuleTseitinSimple(
                    FormuleTseitinSimple::getType(),
                    getOperandeG().distribuerOu(),
                    getOperandeD().distribuerOu()
                );
    else if(ariteDuType(getType())==1)
        return  FormuleTseitinSimple(
                    FormuleTseitinSimple::getType(),
                    getOperandeG().distribuerOu(),
                    getOperandeD().distribuerOu()
                );
    return  FormuleTseitinSimple(
                FormuleTseitinSimple::VARIABLE,
                getName()
            );
}

FormuleTseitinSimple FormuleTseitinSimple::eliminerXor() const
{
    if(getType()==FormuleTseitinSimple::XOR)
    {
        FormuleTseitinSimple equi(
            FormuleTseitinSimple::ET,
            FormuleTseitinSimple(
                FormuleTseitinSimple::OU,
                getOperandeG(),
                getOperandeD()
            ),
            FormuleTseitinSimple(
                FormuleTseitinSimple::OU,
                FormuleTseitinSimple(
                    FormuleTseitinSimple::NON,
                    getOperandeG()
                ),
                FormuleTseitinSimple(
                    FormuleTseitinSimple::NON,
                    getOperandeD()
                )
            )
        );
        return equi.eliminerXor();
    }
    else if(ariteDuType(getType())==2)
        return  FormuleTseitinSimple(
                    FormuleTseitinSimple::getType(),
                    getOperandeG().eliminerXor(),
                    getOperandeD().eliminerXor()
                );
    else if(ariteDuType(getType())==1)
        return  FormuleTseitinSimple(
                    FormuleTseitinSimple::getType(),
                    getOperandeG().eliminerXor(),
                    getOperandeD().eliminerXor()
                );
    return  FormuleTseitinSimple(
                FormuleTseitinSimple::VARIABLE,
                getName()
            );
}

FormuleTseitinSimple FormuleTseitinSimple::eliminerImplique() const
{
    if(getType()==FormuleTseitinSimple::IMPLIQUE)
    {
        FormuleTseitinSimple    equi(
            FormuleTseitinSimple::OU,
            FormuleTseitinSimple(
                FormuleTseitinSimple::NON,
                getOperandeG()
            ),
            getOperandeD()
        );
        return equi.eliminerImplique();
    }
    else if(ariteDuType(getType())==2)
        return  FormuleTseitinSimple(
                    FormuleTseitinSimple::getType(),
                    getOperandeG().eliminerImplique(),
                    getOperandeD().eliminerImplique()
                );
    else if(ariteDuType(getType())==1)
        return  FormuleTseitinSimple(
                    FormuleTseitinSimple::getType(),
                    getOperandeG().eliminerImplique(),
                    getOperandeD().eliminerImplique()
                );
    return  FormuleTseitinSimple(
                FormuleTseitinSimple::VARIABLE,
                getName()
            );
}

FormuleTseitinSimple FormuleTseitinSimple::descendreNon() const
{
    FormuleTseitinSimple op(getOperande());
    FormuleTseitinSimple d;
    FormuleTseitinSimple g;
    switch(op.getType())
    {
    case FormuleTseitinSimple::VARIABLE :
        return FormuleTseitinSimple(FormuleTseitinSimple::NON, op);
    case FormuleTseitinSimple::NON :
        return FormuleTseitinSimple(op.getOperande().getType(), op.getOperande().descendreNon());
    case FormuleTseitinSimple::OU :
        return FormuleTseitinSimple(FormuleTseitinSimple::ET,
                                    FormuleTseitinSimple(FormuleTseitinSimple::NON,getOperande().getOperandeG()),
                                    FormuleTseitinSimple(FormuleTseitinSimple::NON,getOperande().getOperandeD())).descendreNon();
    case FormuleTseitinSimple::ET :
        return FormuleTseitinSimple(FormuleTseitinSimple::OU,
                                    FormuleTseitinSimple(FormuleTseitinSimple::NON,getOperande().getOperandeG()),
                                    FormuleTseitinSimple(FormuleTseitinSimple::NON,getOperande().getOperandeD())).descendreNon();
    case FormuleTseitinSimple::IMPLIQUE :
        return FormuleTseitinSimple(FormuleTseitinSimple::ET,
                                    getOperande().getOperandeG(),
                                    FormuleTseitinSimple(FormuleTseitinSimple::NON,getOperande().getOperandeD())).descendreNon();
    case FormuleTseitinSimple::XOR :
        d = getOperande().getOperandeD().descendreNon();
        g = getOperande().getOperandeG().descendreNon();
        return FormuleTseitinSimple(FormuleTseitinSimple::ET,
                                    FormuleTseitinSimple(FormuleTseitinSimple::OU,
                                            FormuleTseitinSimple(FormuleTseitinSimple::NON,g),
                                            d
                                                        ),
                                    FormuleTseitinSimple(FormuleTseitinSimple::OU,
                                            FormuleTseitinSimple(FormuleTseitinSimple::NON,d),
                                            g
                                                        )
                                   );
        break;
    default :
        throw FormuleTseitinSimpleError( "C'est quoi ton truc ? Tu as vraiment fini l'implémentation ?");
    }
    return *this;
}

FormuleTseitinSimple FormuleTseitinSimple::transformationDeMorgan() const
{
    return eliminerXor().eliminerImplique().descendreNon().distribuerOu();
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
            return "P'tet ben, j'en sais rien..."+(char)(type+48);
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
            return "P'tet ben, j'en sais rien..."+(char)(type+48);
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
            return "P'tet ben, j'en sais rien..."+(char)(type+48);
    }
}
