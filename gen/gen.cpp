#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<sstream>
#include<vector>

using namespace std;

/*string to_string(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}*/

int main(int argc, char* argv[])
{
    int V;
    int C;
    int l;
    int L;

    if(argc<5)
    {
        cout<<"Nombre de variables : ";
        cin>>V;
        cout<<"Nombre de clauses : ";
        cin>>C;
        cout<<"Longueur minimale d'une clause : ";
        cin>>l;
        cout<<"Longueur maximale d'une clause : ";
        cin>>L;
    }
    else
    {
        V=atoi(argv[1]);
        C=atoi(argv[2]);
        l=atoi(argv[3]);
        L=atoi(argv[4]);
    }

    srand(static_cast<unsigned int>(time(NULL)));
    int Ll;
    string filename;
    
    if(argc<6)
    {
        filename="ex_";
        filename+= to_string(V);
        filename+="_";
        filename+= to_string(C);
        filename+="_";
        filename+= to_string(l);
        filename+="_";
        filename+= to_string(L);
        filename+=".cnf";
    }
    else
    {
        filename=argv[5];
    }



    if(L>V)
    {
        cout<<"What ! Tes paramètre incorrects, je m'en badigeonne allègrement les gonades avec le pinceau de l'indifférence !"<<endl;
        exit(EXIT_FAILURE);
    }
    ofstream file(filename);

    file<<"p cnf "<<V<<" "<<C<<'\n';

    vector<int> assignation;
    int pos;
    int pol;

    for(int i=0;i<C;++i)
    {
        Ll=(rand()%(L-l+1))+l;;
        assignation.clear();
        assignation.resize(V,0);
        for(int j=0;j<Ll;++j)
        {
            pos=rand()%V;
            pol=rand()%2;
            for(;assignation[pos]!=0;pos=(pos+1)%V);
            if(pol==1)
                assignation[pos]=1;
            else
                assignation[pos]=-1;
        }

        for(int k=0;k<V;++k)
        {
            if(assignation[k]==1)
                file<<k+1<<" ";
            else if(assignation[k]==-1)
                file<<-k-1<<" ";
        }
        file<<0<<endl;
    }

    file.close();

    return 0;
}
