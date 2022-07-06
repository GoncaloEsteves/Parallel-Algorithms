#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Function responsible for initializing the matrix of incompatibilities.
void initD(int N, int*** D);

//Function responsible for the random distribution of the persons for the rooms.
void randPerm(int N, int*** room, unsigned int myseed);

void clearCache();

void startTimer();

double stopTimer();

#endif