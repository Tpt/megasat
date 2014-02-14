#include<cstdlib>
#include<ctime>
#include"include/Formule.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        cerr << "resol: fatal error: no input files\nresolution terminated." << endl << endl;
        return EXIT_FAILURE;
    }

    Formule formule( argv[1] );
    clock_t t;
    t = clock();
    formule.solve();
    t = clock() - t;
    cout << "c Resolu en : " << static_cast<double>(t) / static_cast<double>(CLOCKS_PER_SEC) << " secondes" << endl;

    return EXIT_SUCCESS;
}
