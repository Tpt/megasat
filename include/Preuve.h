#ifndef PREUVE_H
#define PREUVE_H

#include <vector>

class Preuve
{
public:
    Preuve(const Preuve& other);
    Preuve& operator=(const Preuve& other);
    Preuve(const std::vector<int>& conclusion);
    Preuve(const Preuve& arbre, const std::vector<int>& premisse, int id);
    Preuve(const std::vector<int>& arbre, const std::vector<int>& premisse, int id);
    Preuve(const Preuve& arbre, const std::vector<int>& premisse, const std::vector<int>& conclusion);
    Preuve(const std::vector<std::vector<int>>& conclusions, const std::vector<std::vector<int>>& premisses);
    Preuve(const std::vector<int>& arbre, const std::vector<int>& premisse, const std::vector<int>& conclusion);
    ~Preuve();
    Preuve getResteDeLArbre() const;
    bool isAxiome() const {return premisses.size()==0 && conclusions.size()==1;};
    std::vector<std::vector<int>> getPremisses() const {return premisses;};
    std::vector<std::vector<int>> getConclusions() const {return conclusions;};
    std::vector<int> getPremisse() const {return premisses[premisses.size()-1];};
    std::vector<int> getConclusion() const {return conclusions[conclusions.size()-1];};

private:
    std::vector<int> resolution(const std::vector<int>& c1, const std::vector<int>& c2, int id) const;

    std::vector<std::vector<int>> premisses;
    std::vector<std::vector<int>> conclusions;
};

#endif // PREUVE_H
