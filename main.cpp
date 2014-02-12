#include<cstdlib>
#include<ctime>
#include"CFormule.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc == 1) {
        cerr << "resol: fatal error: no input files\nresolution terminated." << endl << endl;
       return EXIT_FAILURE;
    }

    CFormule formule( argv[1] );
    clock_t t;
    t = clock();
    formule.solve();
    t = clock() - t;
    printf("c Resolu en : %f secondes\n", static_cast<double>(t) / static_cast<double>(CLOCKS_PER_SEC));

    return EXIT_SUCCESS;
}
