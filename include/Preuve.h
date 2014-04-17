#ifndef PREUVE_H
#define PREUVE_H

#include <vector>

class Preuve
{
public:
    Preuve(const Preuve& other);
    Preuve& operator=(const Preuve& other);
    Preuve(const Preuve& arbre, const std::vector<int>& premisse, int id);
    Preuve(const std::vector<int>& arbre, const std::vector<int>& premisse, int id);
    Preuve(const std::vector<std::vector<int>>& conclusions, const std::vector<std::vector<int>>& premisses);
    ~Preuve();
    Preuve getResteDeLArbre() const;
    std::vector<std::vector<int>> getPremisses() const {return premisses;};
    std::vector<std::vector<int>> getConclusions() const {return conclusions;};
    std::vector<int> getPremisse() const {return premisses[premisses.size()-1];};
    std::vector<int> getConclusion() const {return conclusions[conclusions.size()-1];};
    std::vector<int> getLiterauxResolus() const {return literauxResolus;};

    void print() const;

private:
    std::vector<int> resolution(const std::vector<int>& c1, const std::vector<int>& c2, int id) const;
    int difference(const std::vector<int>& c1, const std::vector<int>& c2) const;

    std::vector<std::vector<int>> premisses;
    std::vector<std::vector<int>> conclusions;
    std::vector<int> literauxResolus;
};

#endif // PREUVE_H
