#include "../include/Terme.h"
#include <functional>

using namespace std;

Terme::Terme() : parametres(vector<Terme*>(0)), symbole(""), variable(-1)
{}

Terme::Terme(int variable_) : parametres(vector<Terme*>(0)), symbole(""), variable(variable_)
{}

Terme::Terme(string f, const vector<Terme*>& arguments) :
parametres(arguments), symbole(f), variable(-1)
{}

Terme::Terme(const Terme& F) :
parametres(F.parametres), symbole(F.symbole), variable(F.variable)
{}

Terme& Terme::operator= (const Terme& other)
{
    Terme Temp(other);

    swap(Temp.parametres, this->parametres);
    swap(Temp.symbole, this->symbole);
    swap(Temp.variable, this->variable);

    return *this;
}

Terme::~Terme()
{}

void Terme::free()
{
    for(unsigned int i=0;i<parametres.size();++i)
    {
        parametres[i]->free();
        delete parametres[i];
    }
}

bool Terme::isConflit(Terme t) const
{
    if(t.getParametres().size() * parametres.size() == 0 && t.getParametres().size() + parametres.size()!=0)
        return false;

    if(t.getParametres().size() + parametres.size() == 0)
        return variable != t.getVariable();

    if(t.getParametres().size() != parametres.size())
        return true;

    for(unsigned int i = 0; i < parametres.size(); i++)
        if(parametres[i]->isConflit(*(t.getParametres()[i])))
            return true;

    return false;
}

size_t Terme::hash() const //TODO : mettre le hash en cache dans AtomeCongruance pour éviter trop d'appels ???
{
    size_t hash = std::hash<int>()(variable) + std::hash<string>()(symbole);

    for(unsigned int i = 0; i < parametres.size(); i++)
        hash += parametres[i]->hash() * 31^(i+1);

    return hash;
}

bool Terme::operator==(const Terme& that) const
{
    if( this->symbole != that.symbole || this->variable != that.variable || this->parametres.size() != that.parametres.size() ) {
        return false;
    }

    for(unsigned int i = 0; i < parametres.size(); i++)
        if(!(*this->parametres[i] == *that.parametres[i]))
            return false;

    return true;
}