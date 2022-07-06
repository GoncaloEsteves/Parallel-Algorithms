#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 2000

double tab[N][N] __attribute__((aligned(32)));

double clearcache [30000000];

void clearCache(){
    int i;
    for(i = 0; i < 30000000; i++)
        clearcache[i] = i;
}

void asp(){
    int i, k, j, tmp, tabik;

    #pragma omp parallel for private(i, j, k, tmp, tabik) schedule(dynamic)
    for(i = 0; i < N; i++){
        for(k = 0; k < i; k++){
            tabik = tab[i][k];
            #pragma omp simd
            for(j = 0; j < N; j++){
                tmp = tabik + tab[k][j];
                if(tmp < tab[i][j])
                    tab[i][j] = tmp;
            }
        }
        for(k = k+1; k < N; k++){
            tabik = tab[i][k];
            #pragma omp simd
            for(j = 0; j < N; j++){
                tmp = tabik + tab[k][j];
                if(tmp < tab[i][j])
                    tab[i][j] = tmp;
            }
        }
    }
}

int main(){

	srand(time(NULL));

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            tab[i][j] = rand();
    }

    clearCache();

    double start = omp_get_wtime();
    asp();
    double end = omp_get_wtime();
	double exec_time = (end - start);
    printf("%2f\n", exec_time);

    return 0;
}