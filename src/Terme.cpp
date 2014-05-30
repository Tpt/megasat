#include "../include/Terme.h"
#include <iostream>
#include <functional>

using namespace std;

Terme::Terme() : parametres(vector<Terme>(0)), symbole(""), variable(-1)
{}

Terme::Terme(int variable_) : parametres(vector<Terme>(0)), symbole(""), variable(variable_)
{}

Terme::Terme(string f, const vector<Terme>& arguments) :
parametres(arguments), symbole(f), variable(-1)
{}

Terme::~Terme()
{}

bool Terme::isConflit(Terme t) const
{
    if((t.getParametres().empty() || parametres.empty()) && !(t.getParametres().size() && parametres.empty()))
        return true;

    if(t.getParametres().empty() && parametres.empty())
        return variable != t.getVariable();

    if(t.getParametres().size() != parametres.size())
        return true;

    for(unsigned int i = 0; i < parametres.size(); i++)
        if(parametres[i].isConflit(t.getParametres()[i]))
            return true;

    return false;
}

bool Terme::isConflitInsurmontable(Terme t) const
{
    if((t.getParametres().empty() || parametres.empty()) && !(t.getParametres().size() && parametres.empty()))
    {
        return false;
    }

    if(t.getParametres().empty() && parametres.empty())
    {
        return false;
    }

    if(t.getParametres().size() != parametres.size())
    {
        return true;
    }

    for(unsigned int i = 0; i < parametres.size(); i++)
        if(parametres[i].isConflitInsurmontable(t.getParametres()[i]))
        {
            return true;
        }

    return false;
}

size_t Terme::hash() const
{
    size_t hash_ = std::hash<int>()(variable) + std::hash<string>()(symbole);
    int temp = 1;

    for(unsigned int i = 0; i < parametres.size(); i++)
    {
        temp *= 31;
        hash_ += parametres[i].hash() * static_cast<size_t>(temp);
    }

    return hash_;
}

bool Terme::operator==(const Terme& that) const
{
    if( this->symbole != that.symbole || this->variable != that.variable || this->parametres.size() != that.parametres.size() ) {
        return false;
    }

    for(unsigned int i = 0; i < parametres.size(); i++)
        if(!(this->parametres[i] == that.parametres[i]))
            return false;

    return true;
}

string Terme::toString() const
{
    if(parametres.empty())
        return "x"+to_string(variable);

    string sortie=symbole+"(";
    for(unsigned int i=0;i<parametres.size();++i)
        if(i==0)
            sortie+=parametres[i].toString();
        else
            sortie+=", "+parametres[i].toString();

    return sortie+")";
}
