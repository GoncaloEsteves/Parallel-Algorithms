#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 4096
#define BLOCK_SIZE 8

double A[N][N] __attribute__((aligned(32)));
double B[N][N] __attribute__((aligned(32)));
double C[N][N] __attribute__((aligned(32)));

double clearcache [30000000];

void clearCache(){
    int i;
    for(i = 0; i < 30000000; i++)
        clearcache[i] = i;
}

void matrixMult(){
    int ii, kk, jj, i, k, j;

    #pragma omp parallel for private(ii, kk, jj, i, k, j) schedule(dynamic)
    for(ii = 0; ii < N; ii+=BLOCK_SIZE){
        for(kk = 0; kk < N; kk+=BLOCK_SIZE){
            for(jj = 0; jj < N; jj+=BLOCK_SIZE){
                for(i = ii; i < ii+BLOCK_SIZE; i++){
                    for(k = kk; k < kk+BLOCK_SIZE; k++){
                        #pragma omp simd
                        for(j = jj; j < jj+BLOCK_SIZE; j++)
                            C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
    }
}

int main(){

	srand(time(NULL));

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            A[i][j] = rand();
            B[i][j] = rand();
            C[i][j] = 0;
        }
    }

    clearCache();

    double start = omp_get_wtime();
    matrixMult();
    double end = omp_get_wtime();
	double exec_time = (end - start);
    printf("%2f\n", exec_time);

    return 1;
}