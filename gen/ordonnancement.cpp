#include<iostream>
#include<vector>
#include<tuple>

using namespace std;

typedef struct tache
{
    int d;
    int f;
    int t;
} tache;

int main()
{
    unsigned int N;
    unsigned int M;
    vector<tache> descr;
    vector<pair<int, int>> contraintes;

    cin>>N;
    descr.resize(N);
    for(unsigned int i=0;i<N;++i)
        cin>>descr[i].d>>descr[i].t>>descr[i].f;

    cin>>M;
    contraintes.resize(M, pair<int, int>(0,0));
    for(unsigned int i=0;i<M;++i)
        cin>>contraintes[i].first>>contraintes[i].second;

    for(unsigned int i=0;i<contraintes.size();++i)
    {
        if(i>0)
            cout<<"/\\ ";
        cout<<"x"<<contraintes[i].first-1<<" - x"<<contraintes[i].second-1<<" <= 0 ";
    }

    for(unsigned int i=0;i<N;++i)
    {
        if(i>0 || M>0)
            cout<<"/\\ ";
        cout<<"x"<<i<<" <= "<<descr[i].f - descr[i].t<<" /\\ x"<<i<<" >= "<<descr[i].d;
    }

    for(unsigned int i=0;i<N;++i)
    {
        for(unsigned int j=i+1;j<N;++j)
        {
            cout<<"/\\ (x"<<i<<" - x"<< j << " >= " << descr[j].t << " \\/ x"<< j <<" - x"<< i << " >= " << descr[i].t<<") ";
        }
    }

    cout<<endl;

    return 0;
}
