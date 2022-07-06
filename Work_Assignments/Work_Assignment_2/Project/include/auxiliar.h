#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Function responsible for initializing matrix
void initMatrixes(int N, double*** W);

//Function responsible for initializing matrixes for Jacobian implementation
void initMatrixesJac(int N, double*** U, double*** W);

//Printing a N size matrix
void printMatrix(int N, double*** U);

void clearCache();

void startTimer();

double stopTimer();

#endif