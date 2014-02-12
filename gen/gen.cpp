#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<sstream>

using namespace std;

string to_string(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}

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
    ofstream file(filename);

    file<<"p cnf "<<V<<" "<<C<<'\n';

    for(int i=0;i<C;++i)
    {
        Ll=(rand()%(L-l+1))+l;
        for(int j=0;j<Ll;++j)
        {
            if(rand()%2)
                file<<(rand()%V+1)<<" ";
            else
                file<<-(rand()%V+1)<<" ";
        }
        file<<"0\n";
    }

    file.close();

    return 0;
}
