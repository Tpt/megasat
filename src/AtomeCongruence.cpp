#include "../include/AtomeCongruence.h"
#include<iostream>

using namespace std;

AtomeCongruence::AtomeCongruence() : gauche(Terme()), droite(Terme())
{}

AtomeCongruence::AtomeCongruence(Terme gauche_, Terme droite_) : gauche(gauche_), droite(droite_)
{}

AtomeCongruence::~AtomeCongruence()
{}

bool AtomeCongruence::isConflit() const
{
#ifdef DEBUG
    cout<<"E"<<endl;
#endif
    return gauche.isConflit(droite);
}

bool AtomeCongruence::isConflitInsurmontable() const
{
#ifdef DEBUG
    cout<<"F"<<endl;
#endif
    return gauche.isConflitInsurmontable(droite);
}

size_t AtomeCongruence::hash() const
{
    return this->gauche.hash() + this->droite.hash();
}

bool AtomeCongruence::operator==(const AtomeCongruence& that) const
{
    return (this->gauche == that.gauche && this->droite == that.droite) ||
        (this->gauche == that.droite && this->droite == that.gauche);
}


string AtomeCongruence::toString()
{
#ifdef DEBUG
    cout<<"T"<<endl;
#endif
    string s=gauche.toString();
#ifdef DEBUG
    cout<<"T"<<endl;
#endif
    s+=" = ";
#ifdef DEBUG
    cout<<"T"<<endl;
#endif
    s+=droite.toString();
#ifdef DEBUG
    cout<<"T"<<endl;
#endif
    return s;
}
