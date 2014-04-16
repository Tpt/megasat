#include<vector>
#include<string>
#include<random>

using namespace std;
string genTitle();

string genTitle()
{
    random_device rd;
    vector<string> titles;
    titles.push_back("Une preuve !");
    titles.push_back("De la beauté des preuves mathématiques");
    titles.push_back("A propos du seul arbre qui pousse vers le haut en info");
    titles.push_back("J'aime les pommes de terre");
    titles.push_back("Convex Algebra");
    return titles[rd()%titles.size()];
}
