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
        cout<<"x"<<contraintes[i].first<<" - x"<<contraintes[i].second<<" <= 0 ";
    }

    for(unsigned int i=0;i<N;++i)
    {
        if(i>0 || M>0)
            cout<<"/\\ ";
        cout<<"x"<<i+1<<" <= "<<descr[i].f - descr[i].t<<" /\\ x"<<i+1<<" >= "<<descr[i].d;
    }

    for(unsigned int i=0;i<N;++i)
    {
        for(unsigned int j=i+1;j<N;++j)
        {
            cout<<"/\\ (x"<<i+1<<" - x"<< j+1 << " >= " << descr[j].t << " \\/ x"<< j+1 <<" - x"<< i+1 << " <= " << descr[i].t<<") ";
        }
    }

    cout<<endl;

    return 0;
}
