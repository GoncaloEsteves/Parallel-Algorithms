#include "../include/poisson.h"
#include "../include/auxiliar.h"

int poissonGS(int N, double*** W){
    int i, j;
    double n;
    double TOL = 1.0/((N-1)*(N-1));
    int ITER = 0;
    double DIFF = TOL + 1;

    while (DIFF > TOL){
        DIFF = 0;

        for(i = 1; i < N-1; i++){
            for(j = 1; j < N-1; j++){
                n = (*W)[i][j];
                (*W)[i][j] = ((*W)[i-1][j] + (*W)[i][j-1] + (*W)[i][j+1] + (*W)[i+1][j]) / 4;
                
                if(fabs(((*W)[i][j] - n)) > DIFF)
                    DIFF = fabs(((*W)[i][j] - n));
            }
        }

        ITER++; 
    }

    return ITER;
}