#include "../include/Preuve.h"
#include<set>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

Preuve::Preuve(const Preuve& arbre, const vector<int>& premisse, int id) :
premisses(arbre.getPremisses()), conclusions(arbre.getConclusions()), literauxResolus(arbre.literauxResolus)
{
    premisses.push_back(premisse);
    conclusions.push_back(resolution(premisse, arbre.getConclusion(), id));
    literauxResolus.push_back(id);
}

Preuve::Preuve(const vector<int>& conclusion, const vector<int>& premisse, int id) :
premisses(vector<vector<int>>(1,premisse)), conclusions(vector<vector<int>>(1,conclusion)), literauxResolus(vector<int>(1,id))
{
    conclusions.push_back(resolution(premisse, conclusion, id));
}

Preuve::Preuve(const Preuve& other) :
premisses(other.premisses), conclusions(other.conclusions), literauxResolus(other.literauxResolus)
{}

Preuve& Preuve::operator= (const Preuve& other)
{
    Preuve Temp(other);

    swap(Temp.premisses, this->premisses);
    swap(Temp.conclusions, this->conclusions);
    swap(Temp.literauxResolus, this->literauxResolus);

    return *this;
}

Preuve::Preuve(const std::vector<std::vector<int>>& conclusions_, const std::vector<std::vector<int>>& premisses_) :
premisses(premisses_), conclusions(conclusions_), literauxResolus(vector<int>())
{
    if(premisses_.size() > conclusions_.size())
    {
        premisses = conclusions_;
        conclusions = premisses_;
    }

    for(unsigned int i=0;i<premisses.size();++i)
    {
        literauxResolus.push_back(difference(premisses[i],conclusions[i+1]));
    }

}

Preuve::~Preuve()
{}

int Preuve::difference(const vector<int>& c1, const vector<int>& c2) const ///premisse, conclusion
{
    for(int e : c1)
        if(find(c2.begin(), c2.end(), e)==c2.end())
            return e;

    return 0;
}

void Preuve::print() const
{
    for(unsigned int i=0;i<premisses.size();++i)
    {
        for(unsigned int j=0;j<conclusions[i].size();++j)
            cout<<conclusions[i][j]<<" ";

        cout<<"    ";

        for(unsigned int j=0;j<premisses[i].size();++j)
            cout<<premisses[i][j]<<" ";

        cout<<"    "<<literauxResolus[i]<<endl;

    }

    for(unsigned int j=0;j<conclusions[premisses.size()].size();++j)
        cout<<conclusions[premisses.size()][j]<<" ";

    cout<<endl;


    cout<<endl<<endl;
}

vector<int> Preuve::resolution(const vector<int>& c1, const vector<int>& c2, int id) const
{
    set<int> temp;

    for(int literal : c1)
        if(literal != id && literal != -id)
            temp.insert(literal);

    for(int literal : c2)
        if(literal != id && literal != -id)
            temp.insert(literal);

    vector<int> sortie;

    for(int literal : temp)
        sortie.push_back(literal);

    return sortie;
}
