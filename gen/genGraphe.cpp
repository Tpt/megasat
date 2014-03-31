#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<sstream>
#include<vector>
#include<unordered_set>

using namespace std;

/*string to_string(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}*/

pair<int, int> next(int n, pair<int, int> e);

pair<int, int> next(int n, pair<int, int> e)
{
    if(e.second<n-1)
    {
        e.second++;
        return e;
    }
    else if(e.first<n-2)
        e.first++;
    else
        e.first=1;
    
    e.second=e.first+1;
    return e;
}

int main(int argc, char* argv[])
{
    int n;
    int m;
    
    if(argc<3)
    {
        cout<<"Nombre de sommets : ";
        cin>>n;
        cout<<"Nombre d'arêtes': ";
        cin>>m;
    }
    else
    {
        n=atoi(argv[1]);
        m=atoi(argv[2]);
    }
    
    if(n*(n-1)<2*m)
    {
        cerr<<"Trop d'arêtes ! "<<endl;
        return EXIT_FAILURE;
    }

    srand(static_cast<unsigned int>(time(NULL)));
    string filename;

    if(argc<4)
    {
        filename="graphe_";
        filename+= to_string(n);
        filename+="_";
        filename+= to_string(m);
        filename+=".col";
    }
    else
    {
        filename=argv[3];
    }


    ofstream file(filename);


    vector<unordered_set<int>> adj(n);
    pair<int, int> e;
    
    for(int i=0;i<m;++i)
    {
        e.first=rand()%(n-1);
        e.second=(rand()%(n-1-e.first))+e.first+1;
        for(;adj[e.first].find(e.second)!=adj[e.first].end();e=next(n,e));
        adj[e.first].insert(e.second);
    }
    
    file<<"c Créé aléatoirement par notre superbe programme de génération de graphe"<<endl;
    file<<"c Il contient "<<n<<" sommets et "<<m<<" arêtes distinctes."<<endl;
    file<<"c Passez le bonjour à MM Blot et Hirschkoff"<<endl;
    file<<"p edge "<<n<<" "<<m<<endl;    

    for(int i=0;i<n;++i)
    {
        for(int w : adj[i])
        {
            file<<"e "<<i+1<<" "<<w+1<<endl;
        }
    }
    

    file.close();

    return 0;
}
