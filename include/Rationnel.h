#ifndef RATIONNEL_H_INCLUDED
#define RATIONNEL_H_INCLUDED

#include<gmpxx.h>

class Rationnel
{
public:
    Rationnel();
    Rationnel(mpz_class numerateur, mpz_class denominateur);
    ~Rationnel();
    mpz_class getNumerateur() const __attribute__((pure));
    mpz_class getDenominateur() const __attribute__((pure));
    Rationnel& power(unsigned long int exposant) __attribute__((pure));
    void simplifier() __attribute__((pure));
    Rationnel& operator+=(const Rationnel& a);

private:
    mpz_class numerateur;
    mpz_class denominateur;
};

bool operator<(Rationnel& lhs, Rationnel& rhs);

#endif // RATIONNEL_H_INCLUDED
