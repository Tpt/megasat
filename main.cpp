#include<cstdlib>
#include<ctime>
#include"CFormule.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc==1)
    {
        cerr<<"resol: fatal error: no input files\nresolution terminated."<<endl<<endl;
        exit(EXIT_FAILURE);
    }

    CFormule* formule=new CFormule(argv[1]);
    clock_t t;
    t=clock();
    formule->solve();
    t=clock()-t;
    printf("c Resolu en : %f secondes\n",static_cast<double>(t)/static_cast<double>(1000));
    return 0;
}
