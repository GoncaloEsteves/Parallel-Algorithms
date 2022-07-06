#include "../include/auxiliar.h"

double clearcache[30000000];
double initime;

void initMatrixes(int N, double*** W){
    (*W) = (double**) malloc(sizeof(double*) * N);

    for(int i = 0; i < N; i++){
        (*W)[i] = (double*) malloc(sizeof(double) * N);

        for(int j = 0; j < N; j++){
            if (i == N-1){
                (*W)[i][j] = 0;
            }
            else if( (i==0) || (j==0) || (j==(N-1)) ){
                (*W)[i][j] = 100;
            }
            else{
                (*W)[i][j] = 50;
            } 
        }
    }
}

void initMatrixesJac(int N, double*** U, double*** W){
    (*U) = (double**) malloc(sizeof(double*) * N);
    (*W) = (double**) malloc(sizeof(double*) * N);

    for(int i = 0; i < N; i++){
        (*U)[i] = (double*) malloc(sizeof(double) * N);
        (*W)[i] = (double*) malloc(sizeof(double) * N);

        for(int j = 0; j < N; j++){
            if (i == N-1){
                (*U)[i][j] = 0;
                (*W)[i][j] = 0;
            }
            else if( (i==0) || (j==0) || (j==(N-1)) ){
                (*U)[i][j] = 100;
                (*W)[i][j] = 100;
            }
            else
                (*U)[i][j] = 50; 
        }
    }
}

void printMatrix(int N, double*** U){
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
             printf("%2f     ", (*U)[i][j]);
        }
        printf("\n");
    }
}


void clearCache(){
    for(int i = 0; i < 30000000; i++)
        clearcache[i] = i;
}

void startTimer(){
    double aux = omp_get_wtime();
    initime = aux * 100000;
}

double stopTimer(){
    double aux = omp_get_wtime();
    double aux2 = aux * 100000;
    return (aux2 - initime);
}