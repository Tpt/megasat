#include "../include/Connecteurs.h"

using namespace std;

FormuleTseitin::~FormuleTseitin()
{}

ConnecteurBinaire::~ConnecteurBinaire()
{}

ConnecteurUnaire::~ConnecteurUnaire()
{}

FormuleTseitin* VariablePropositionnelle::simplifier()
{
    return new VariablePropositionnelle(name);//return this
}

FormuleTseitin::FormuleType VariablePropositionnelle::getType()
{
    return FormuleTseitin::VARIABLE;
}


FormuleTseitin* ConnecteurBinaire::getOperandeG() const
{
    return &operandeG;
}

FormuleTseitin* ConnecteurBinaire::getOperandeD() const
{
    return &operandeD;
}

FormuleTseitin* ConnecteurUnaire::getOperande() const
{
    return &operande;
}



FormuleTseitin* Et::simplifier()
{
    return new Et(&operandeG, &operandeD); //return this
}

FormuleTseitin::FormuleType Et::getType()
{
    return FormuleTseitin::ET;
}



FormuleTseitin* Ou::simplifier()
{
    return new Ou(&operandeG, &operandeD); ///TODO
}

FormuleTseitin::FormuleType Ou::getType()
{
    return FormuleTseitin::OU;
}



FormuleTseitin* Xor::simplifier()
{
    return new Xor(&operandeG, &operandeD); ///TODO
}

FormuleTseitin::FormuleType Xor::getType()
{
    return FormuleTseitin::XOR;
}



FormuleTseitin* Implique::simplifier()
{
    return new Implique(&operandeG, &operandeD); ///TODO
}

FormuleTseitin::FormuleType Implique::getType()
{
    return FormuleTseitin::IMPLIQUE;
}



FormuleTseitin* Non::simplifier()
{
    switch(operande.getType())
    {
        case FormuleType::OU :
        {
            Non g ((dynamic_cast<Ou*>(&operande))->getOperandeG());
            Non d ((dynamic_cast<Ou*>(&operande))->getOperandeD());
            return Et(dynamic_cast<FormuleTseitin*>(&g), dynamic_cast<FormuleTseitin*>(&d)).simplifier();
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

FormuleTseitin::FormuleType Non::getType()
{
    return FormuleTseitin::NON;
}
