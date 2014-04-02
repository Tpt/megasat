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

string next_string(string s);
string gen(int prof_min, int prof_max, vector<string>& vars);

string next_string(string s)
{
    for(unsigned int i=0;i<s.size();++i)
        if(s[i]=='z')
            s[i]='a';
        else
        {
            s[i]++;
            return s;
        }
    
    s=s+"a";
    return s;
}

string gen(int prof_min, int prof_max, vector<string>& vars)
{
    if(prof_max==0)
        return vars[rand()%vars.size()];
    
    if(prof_min<0)
    {
        switch(rand()%5)
        {
            case 0:
                return "("+gen(prof_min-1,prof_max-1,vars)+"=>"+gen(prof_min-1,prof_max-1,vars)+")";
            case 1:
                return "("+gen(prof_min-1,prof_max-1,vars)+"/\\"+gen(prof_min-1,prof_max-1,vars)+")";
            case 2:
                return "("+gen(prof_min-1,prof_max-1,vars)+"\\/"+gen(prof_min-1,prof_max-1,vars)+")";
            case 3:
                return "~"+gen(prof_min-1,prof_max-1,vars);
            default:
                return vars[rand()%vars.size()];
        }
    }
    switch(rand()%4)
    {
        case 0:
            return "("+gen(prof_min-1,prof_max-1,vars)+"=>"+gen(prof_min-1,prof_max-1,vars)+")";
        case 1:
            return "("+gen(prof_min-1,prof_max-1,vars)+"/\\"+gen(prof_min-1,prof_max-1,vars)+")";
        case 2:
            return "("+gen(prof_min-1,prof_max-1,vars)+"\\/"+gen(prof_min-1,prof_max-1,vars)+")";
        default:
            return "~"+gen(prof_min-1,prof_max-1,vars);
    }
}

int main(int argc, char* argv[])
{
    int V;
    int p;
    int P;

    if(argc<4)
    {
        cout<<"Nombre de variables : ";
        cin>>V;
        cout<<"Profondeur minimale : ";
        cin>>p;
        cout<<"Profondeur maximale : ";
        cin>>P;
    }
    else
    {
        V=atoi(argv[1]);
        p=atoi(argv[2]);
        P=atoi(argv[3]);
    }

    srand(static_cast<unsigned int>(time(NULL)));
    string filename;

    if(argc<5)
    {
        filename="tseitin_";
        filename+= to_string(V);
        filename+="_";
        filename+= to_string(p);
        filename+="_";
        filename+= to_string(P);
        filename+=".txt";
    }
    else
    {
        filename=argv[4];
    }


    ofstream file(filename);

    vector<string> vars;
    string s="a";
    
    for(int i=0;i<V;++i)
    {
        vars.push_back(s);
        s=next_string(s);
    }
    

    file<<gen(p,P,vars)<<endl;

    file.close();

    return 0;
}
