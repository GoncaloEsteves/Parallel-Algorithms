#include "../include/auxiliar.h"

double clearcache[30000000];
double initime;

void initD(int N, int*** D){
    int i, j, aux;
    (*D) = malloc(sizeof(int*) * N);

    for(i = 0; i < N; i++)
        (*D)[i] = malloc(sizeof(int) * N);

    for(i = 0; i < N; i++){
        (*D)[i][i] = 0;

        for(j = i+1; j < N; j++){
            aux = ((rand())%10) + 1;
            (*D)[i][j] = aux;
            (*D)[j][i] = aux;
        }
    }
}

void randPerm(int N, int*** room, unsigned int myseed){
    int i, N2, a , b , c, d, aux;
    N2 = N/2;
    (*room) = malloc(sizeof(int*) * N2);

    for(i = 0; i < N2; i++){
        (*room)[i] = malloc(sizeof(int) * 2);

        (*room)[i][0] = i*2;
        (*room)[i][1] = (i*2)+1;
    }
    
    for(i = 0; i < N2; i++){
        a = (rand_r(&myseed))%N2;
        b = (rand_r(&myseed))%N2;
        c = (rand_r(&myseed))%2;
        d = (rand_r(&myseed))%2;

        aux = (*room)[i][0];
        (*room)[i][0] = (*room)[a][c];
        (*room)[a][c] = aux;

        aux = (*room)[i][1];
        (*room)[i][1] = (*room)[b][d];
        (*room)[b][d] = aux;
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