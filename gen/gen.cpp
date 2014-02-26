#include<iostream>
#include<fstream>
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

    srand(static_cast<long int>(time(NULL)));
    int Ll;
    string filename("ex_");
    filename+= to_string(V);
    filename+="_";
    filename+= to_string(C);
    filename+="_";
    filename+= to_string(l);
    filename+="_";
    filename+= to_string(L);
    filename+=".cnf";


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
        assignation.resize(Ll,0);
        for(int j=0;j<Ll;++j)
        {
            pos=rand()%Ll;
            pol=rand()%2;
            for(;assignation[pos]!=0;pos=(pos+1)%Ll);
            if(pol)
                assignation[pos]=1;
            else
                assignation[pos]=0;
        }

        for(int k=0;k<Ll;++k)
        {
            if(assignation[k]==1)
                file<<k+1<<" ";
            else
                file<<-k-1<<" ";
        }
        file<<0<<endl;
    }

    file.close();

    return 0;
}
