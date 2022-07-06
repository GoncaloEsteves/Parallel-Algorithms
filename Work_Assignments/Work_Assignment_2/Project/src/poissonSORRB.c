#include "../include/poisson.h"
#include "../include/auxiliar.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

int poissonSORRBSeq(int N, double*** W){
    int i, j;
    double p, n;
    double TOL = 1.0/((N-1)*(N-1));
    int ITER = 0;
    double DIFF = TOL + 1;  
    
    p = 2 /(1 + sin(M_PI/(N-1)));

    while (DIFF > TOL){
        DIFF = 0;

        for(i = 1; i < N-1; i++){
            for(j = 1+ ((i)%2); j < N-1; j+=2){
                n = (*W)[i][j];
                (*W)[i][j] = (1-p) * (*W)[i][j] + p * ((*W)[i-1][j] + (*W)[i][j-1] + (*W)[i][j+1] + (*W)[i+1][j]) / 4;
                
                if( fabs(((*W)[i][j] - n)) > DIFF )
                    DIFF = fabs(((*W)[i][j] - n));
            }
        }
        for(i = 1; i < N-1; i++){
            for(j = 1+ ((i+1)%2); j < N-1; j+=2){
                n = (*W)[i][j];
                (*W)[i][j] = (1-p) * (*W)[i][j] + p * ((*W)[i-1][j] + (*W)[i][j-1] + (*W)[i][j+1] + (*W)[i+1][j]) / 4;

                if( fabs(((*W)[i][j] - n)) > DIFF )
                    DIFF = fabs(((*W)[i][j] - n));
            }
        }

        ITER++; 
    }

    return ITER;
}

int poissonSORRBPar(int N, double*** W){
    int i, j;
    double p, n;
    double TOL = 1.0/((N-1)*(N-1));
    int ITER = 0;
    double DIFF = TOL + 1;  
    
    p = 2 /(1 + sin(M_PI/(N-1)));

    int threads, id;
    double* DIFFAux;

    #pragma omp parallel
    {
        #pragma omp single
        {
            threads = omp_get_num_threads();
            DIFFAux = malloc(sizeof(double) * threads);
        }
    }

    while (DIFF > TOL){
        DIFF = 0;
        
        #pragma omp parallel
        {
            id = omp_get_thread_num();
            DIFFAux[id] = 0;

            #pragma omp for
            for(i = 1; i < N-1; i++){
                for(j = 1+(i%2); j < N-1; j+=2){
                    n = (*W)[i][j];
                    (*W)[i][j] = (1-p) * (*W)[i][j] + p * ((*W)[i-1][j] + (*W)[i][j-1] + (*W)[i][j+1] + (*W)[i+1][j]) / 4;
                
                    if(fabs(((*W)[i][j] - n)) > DIFFAux[id])
                        DIFFAux[id] = fabs(((*W)[i][j] - n));
                }
            }
        
            #pragma omp for
            for(i = 1; i < N-1; i++){
                for(j = 1+((i+1)%2); j < N-1; j+=2){
                    n = (*W)[i][j];
                    (*W)[i][j] = (1-p) * (*W)[i][j] + p * ((*W)[i-1][j] + (*W)[i][j-1] + (*W)[i][j+1] + (*W)[i+1][j]) / 4;

                    if(fabs(((*W)[i][j] - n)) > DIFFAux[id])
                        DIFFAux[id] = fabs(((*W)[i][j] - n));
                }
            }
        }

        for(i = 0; i < threads; i++){
            if(DIFFAux[i] > DIFF)
                DIFF = DIFFAux[i];
        }

        ITER++;
    }

    return ITER;
}