#include "../include/Preuve.h"
#include<unordered_set>
#include<cmath>

using namespace std;

Preuve::Preuve(const Preuve& arbre, const vector<int>& premisse, int id) :
premisses(arbre.getPremisses()), conclusions(arbre.getConclusions())
{
    premisses.push_back(premisse);
    conclusions.push_back(resolution(premisse, arbre.getConclusion(), id));
}

Preuve::Preuve(const vector<int>& conclusion, const vector<int>& premisse, int id) :
premisses(vector<vector<int>>(1,premisse)), conclusions(vector<vector<int>>(1,conclusion))
{
    conclusions.push_back(resolution(premisse, conclusion, id));
}

Preuve::Preuve(const Preuve& arbre, const vector<int>& premisse, const vector<int>& conclusion) :
premisses(arbre.getPremisses()), conclusions(arbre.getConclusions())
{
    premisses.push_back(premisse);
    conclusions.push_back(conclusion);
}

Preuve::Preuve(const vector<int>& arbre, const vector<int>& premisse, const vector<int>& conclusion) :
premisses(vector<vector<int>>(1,premisse)), conclusions(vector<vector<int>>(1,arbre))
{
    conclusions.push_back(conclusion);
}

Preuve::Preuve(const vector<int>& arbre) :
premisses(vector<vector<int>>()), conclusions(vector<vector<int>>(1,arbre))
{}

Preuve::Preuve(const Preuve& other) :
premisses(other.premisses), conclusions(other.conclusions)
{}

Preuve& Preuve::operator= (const Preuve& other)
{
    Preuve Temp(other);

    swap(Temp.premisses, this->premisses);
    swap(Temp.conclusions, this->conclusions);

    return *this;
}

Preuve::Preuve(const std::vector<std::vector<int>>& conclusions_, const std::vector<std::vector<int>>& premisses_) :
premisses(premisses_), conclusions(conclusions_)
{
    if(premisses_.size()>conclusions_.size())
    {
        premisses=conclusions_;
        conclusions=premisses_;
    }
}

Preuve::~Preuve()
{}

vector<int> Preuve::resolution(const vector<int>& c1, const vector<int>& c2, int id) const
{
    unordered_set<int> temp;

    for(int literal : c1)
        if(literal!=id && literal!=-id)
            temp.insert(literal);

    for(int literal : c2)
        if(literal!=id && literal!=-id)
            temp.insert(literal);

    vector<int> sortie;

    for(int literal : temp)
        sortie.push_back(literal);

    return sortie;

}

Preuve Preuve::getResteDeLArbre() const
{
    vector<vector<int>> premisses_temp=premisses;
    vector<vector<int>> conclusions_temp=conclusions;

    premisses_temp.pop_back();
    conclusions_temp.pop_back();

    return Preuve(conclusions_temp, premisses_temp);
}
