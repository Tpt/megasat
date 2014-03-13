#include "../include/Connecteurs.h"

using namespace std;
/*
FormuleTseitin::~FormuleTseitin()
{}

ConnecteurBinaire::~ConnecteurBinaire()
{}

ConnecteurUnaire::~ConnecteurUnaire()
{}

FormuleTseitin& VariablePropositionnelle::simplifier()
{
    return *(dynamic_cast<FormuleTseitin*>(new VariablePropositionnelle(name)));//return this
}

FormuleTseitin::FormuleType VariablePropositionnelle::getType()
{
    return FormuleTseitin::VARIABLE;
}


FormuleTseitin& ConnecteurBinaire::getOperandeG() const
{
    return operandeG;
}

FormuleTseitin& ConnecteurBinaire::getOperandeD() const
{
    return operandeD;
}

FormuleTseitin& ConnecteurUnaire::getOperande() const
{
    return operande;
}



FormuleTseitin& Et::simplifier()
{
    return *(dynamic_cast<FormuleTseitin*>(new Et(operandeG.simplifier(), operandeD.simplifier())));
}

FormuleTseitin::FormuleType Et::getType()
{
    return FormuleTseitin::ET;
}



FormuleTseitin& Ou::simplifier()
{
    return *(dynamic_cast<FormuleTseitin*>(new Ou(operandeG, operandeD)));
}

FormuleTseitin::FormuleType Ou::getType()
{
    return FormuleTseitin::OU;
}



FormuleTseitin& Xor::simplifier()
{
    return *(dynamic_cast<FormuleTseitin*>(new Xor(operandeG, operandeD)));///TODO
}

FormuleTseitin::FormuleType Xor::getType()
{
    return FormuleTseitin::XOR;
}



FormuleTseitin& Implique::simplifier()
{
    return *(dynamic_cast<FormuleTseitin*>(new Implique(operandeG, operandeD)));///TODO
}

FormuleTseitin::FormuleType Implique::getType()
{
    return FormuleTseitin::IMPLIQUE;
}



FormuleTseitin& Non::simplifier()
{
    switch(operande.getType())
    {
        case FormuleType::OU :
        {
            Non g ((dynamic_cast<Ou*>(&operande))->getOperandeG());
            Non d ((dynamic_cast<Ou*>(&operande))->getOperandeD());
            Et* et = new Et(g.simplifier(), d.simplifier());
            FormuleTseitin& sortie (*(dynamic_cast<FormuleTseitin*>(et)));
            delete et;
            return sortie;
        }
        case FormuleType::ET :
        {
            Non g ((dynamic_cast<Et*>(&operande))->getOperandeG());
            Non d ((dynamic_cast<Et*>(&operande))->getOperandeD());
            return Ou(dynamic_cast<FormuleTseitin*>(&g), dynamic_cast<FormuleTseitin*>(&d)).simplifier();
        }
        case FormuleType::VARIABLE :
        {
            return &operande;
        }
        case FormuleType::IMPLIQUE :
        {
            Non d ((dynamic_cast<Implique*>(&operande))->getOperandeD());
            return Et((dynamic_cast<Implique*>(&operande))->getOperandeG(), dynamic_cast<FormuleTseitin*>(&d)).simplifier();
        }
        case FormuleType::XOR :
        {
            FormuleTseitin* a ((dynamic_cast<Xor*>(&operande))->getOperandeG());
            FormuleTseitin* b ((dynamic_cast<Xor*>(&operande))->getOperandeD());
            Non* pA = new Non(a);
            Non* pB = new Non(b);
            FormuleTseitin* non_a (dynamic_cast<FormuleTseitin*>(pA));
            FormuleTseitin* non_b (dynamic_cast<FormuleTseitin*>(pB));
            Ou* pANB = new Ou(a,non_b);
            Ou* pNAB = new Ou(non_a,b);
            FormuleTseitin* g (dynamic_cast<FormuleTseitin*>(pANB));
            FormuleTseitin* d (dynamic_cast<FormuleTseitin*>(pNAB));

            delete pA;
            delete pB;
            delete g;
            delete d;
            return Et(g,d).simplifier();
        }
        case FormuleType::NON : {
            return ((dynamic_cast<Non*>(&operande))->getOperande()->simplifier());
        }
        default :
        {

        }

    }

    return new Non(&operande); //return this
}

FormuleTseitin::FormuleType Non::getType() const
{
    return FormuleTseitin::NON;
}*/

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
operandeG(F.operandeG), operandeD(F.operandeD), type(FormuleTseitinSimple::VARIABLE), name("")
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
    if(type_!=FormuleTseitinSimple::VARIABLE)
        throw FormuleTseitinSimpleError( "Le type devrait être une variable !");

    type=FormuleTseitinSimple::VARIABLE;
    name=name_;
}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple op) :
    operandeG(nullptr), operandeD(nullptr), type(FormuleTseitinSimple::VARIABLE), name("")
{
    if(ariteDuType(type_)!=1)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 1 !");

    type=FormuleTseitinSimple::NON;
    *operandeG=op;
}

FormuleTseitinSimple::FormuleTseitinSimple(FormuleTypeSimple type_, FormuleTseitinSimple opG, FormuleTseitinSimple opD) :
    operandeG(nullptr), operandeD(nullptr), type(FormuleTseitinSimple::VARIABLE), name("")
{
    if(ariteDuType(type_)!=2)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 2 !");

    type=type_;
    *operandeG=opG;
    *operandeD=opD;
}

FormuleTseitinSimple::~FormuleTseitinSimple()
{
    delete operandeD;
    delete operandeG;
}

string FormuleTseitinSimple::getName() const
{
    return name;
}

FormuleTseitinSimple FormuleTseitinSimple::getOperandeG() const
{
    if(getArite()!=2)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 2 !");
    return *operandeG;
}

FormuleTseitinSimple FormuleTseitinSimple::getOperandeD() const
{
    if(getArite()!=2)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 2 !");
    return *operandeD;
}

FormuleTseitinSimple FormuleTseitinSimple::getOperande() const
{
    if(getArite()!=1)
        throw FormuleTseitinSimpleError( "Le type devrait avoir une arité 1 !");
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

FormuleTseitinSimple FormuleTseitinSimple::normaliser() const
{
    return eliminerXor().eliminerImplique().descendreNon().distribuerOu();
}
