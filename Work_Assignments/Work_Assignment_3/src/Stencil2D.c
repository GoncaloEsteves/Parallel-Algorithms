#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 2000
#define BLOCK_SIZE 8

double G[N][N]  __attribute__((aligned(32)));

double clearcache [30000000];

void clearCache(){
    int i;
    for(i = 0; i < 30000000; i++)
        clearcache[i] = i;
}

void stencil2D(){
    int ii, jj, i, j, k = 0, N_1 = N-1, maxi, maxj;
    double cons = 0.2;

    while(k < 1000){

        #pragma omp parallel for private(ii, jj, i, j, maxi, maxj) schedule(static)
        for(ii = 1; ii < N_1; ii+=BLOCK_SIZE){
            maxi = (N_1 > ii+BLOCK_SIZE) ? (ii+BLOCK_SIZE) : N_1;
            for(jj = 1+(ii&1); jj < N_1; jj+=BLOCK_SIZE){
                maxj = (N_1 > jj+BLOCK_SIZE) ? (jj+BLOCK_SIZE) : N_1;
                for(i = ii; i < maxi; i++){
                    for(j = jj; j < maxj; j+=2)
                        G[i][j] = (G[i][j] + G[i][j+1] + G[i][j-1] + G[i+1][j] + G[i-1][j]) * cons;
                }
            }
        }

        #pragma omp parallel for private(ii, jj, i, j, maxi, maxj) schedule(static)
        for(ii = 1; ii < N_1; ii+=BLOCK_SIZE){
            maxi = (N_1 > ii+BLOCK_SIZE) ? (ii+BLOCK_SIZE) : N_1;
            for(jj = 1+((ii+1)&1); jj < N_1; jj+=BLOCK_SIZE){
                maxj = (N_1 > jj+BLOCK_SIZE) ? (jj+BLOCK_SIZE) : N_1;
                for(i = ii; i < maxi; i++){
                    for(j = jj; j < maxj; j+=2)
                        G[i][j] = (G[i][j] + G[i][j+1] + G[i][j-1] + G[i+1][j] + G[i-1][j]) * cons;
                }
            }
        }

        k++;
    }
}

int main(){

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if (i == N-1){
                G[i][j] = 0;
            }
            else if( (i==0) || (j==0) || (j==(N-1)) ){
                G[i][j] = 100;
            }
            else{
                G[i][j] = 50;
            } 
        }
    }

    clearCache();

    double start = omp_get_wtime();
    stencil2D();
    double end = omp_get_wtime();
	double exec_time = (end - start);
    printf("%2f\n", exec_time);

    return 1;
}