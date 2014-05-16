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
    if(t.getParametres().size() * parametres.size() == 0 && t.getParametres().size() + parametres.size()!=0)
        return true;

    if(t.getParametres().size() + parametres.size() == 0)
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
    if(t.getParametres().size() * parametres.size() == 0 && t.getParametres().size() + parametres.size()!=0)
    {
#ifdef DEBUG
        cout<<"1"<<endl;
#endif
        return false;
    }

    if(t.getParametres().size() + parametres.size() == 0)
    {
#ifdef DEBUG
        cout<<"2"<<endl;
#endif
        return false;
    }

    if(t.getParametres().size() != parametres.size())
    {
#ifdef DEBUG
        cout<<"3"<<endl;
#endif
        return true;
    }

    for(unsigned int i = 0; i < parametres.size(); i++)
        if(parametres[i].isConflitInsurmontable(t.getParametres()[i]))
        {
#ifdef DEBUG
            cout<<"4"<<endl;
#endif
            return true;
        }

#ifdef DEBUG
    cout<<"5"<<endl;
#endif
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

string Terme::toString()
{
#ifdef DEBUG
    cout<<"S: "<<parametres.size()<<endl;
#endif
    if(parametres.size()==0)
        return "x_"+to_string(variable);

    string sortie=symbole+"(";
    for(unsigned int i=0;i<parametres.size();++i)
        if(i==0)
            sortie+=parametres[i].toString();
        else
            sortie+=", "+parametres[i].toString();

    return sortie+")";
}
