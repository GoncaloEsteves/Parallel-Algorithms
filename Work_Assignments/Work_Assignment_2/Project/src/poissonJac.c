#include "../include/poisson.h"
#include "../include/auxiliar.h"

int poissonJac(int N, double*** U, double*** W){
    int i, j;
    double TOL = 1.0/((N-1)*(N-1));
    int ITER = 0;
    double DIFF = TOL + 1;

    while (DIFF > TOL){
        DIFF = 0;

        for(i = 1; i < N-1; i++)
            for(j = 1; j < N-1; j++){
                (*W)[i][j] = ((*U)[i-1][j] + (*U)[i][j-1] + (*U)[i][j+1] + (*U)[i+1][j]) / 4;
                
                if(fabs(((*W)[i][j] - (*U)[i][j])) > DIFF)
                    DIFF = fabs(((*W)[i][j] - (*U)[i][j]));
            }

         for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                (*U)[i][j] = (*W)[i][j];

        ITER++; 
    }

    return ITER;
}