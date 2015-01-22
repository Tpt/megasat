#include "../include/Rationnel.h"

Rationnel::Rationnel() :
numerateur(0), denominateur(1)
{}

Rationnel::Rationnel(mpz_class numerateur_, mpz_class denominateur_) :
numerateur(numerateur_), denominateur(denominateur_)
{}

Rationnel::~Rationnel()
{}

mpz_class Rationnel::getNumerateur() const
{
    return numerateur;
}

mpz_class Rationnel::getDenominateur() const
{
    return denominateur;
}


Rationnel& Rationnel::power(unsigned long int exposant)
{
    mpz_pow_ui(numerateur.get_mpz_t(), numerateur.get_mpz_t(), exposant);
    mpz_pow_ui(denominateur.get_mpz_t(), denominateur.get_mpz_t(), exposant);

    return *this;
}

void Rationnel::simplifier()
{
    mpz_class d;
    mpz_gcd(d.get_mpz_t(), numerateur.get_mpz_t(), denominateur.get_mpz_t());
    numerateur /= d;
    denominateur /= d;
}

Rationnel& Rationnel::operator+=(const Rationnel& a)
{
    mpz_class nouveauNumerateur = numerateur*a.denominateur + denominateur*a.numerateur;
    mpz_class nouveauDenominateur = denominateur*a.denominateur;

    numerateur = nouveauNumerateur;
    denominateur = nouveauDenominateur;

    simplifier();

    return *this;
}

bool operator<(Rationnel& lhs, Rationnel& rhs)
{
    return lhs.getNumerateur()*rhs.getDenominateur()< rhs.getNumerateur()*lhs.getDenominateur();
}
