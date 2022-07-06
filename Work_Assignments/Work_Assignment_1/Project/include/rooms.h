#ifndef ROOMS_H
#define ROOMS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include "auxiliar.h"

/*
    These functions are used in order to allocate N persons into N/2 rooms,
    in a way that minimizes the potential conflicts between the occupants of the same room.
    Despite this, all of them use different methods to obtain the final answer.
*/

// Implementation in which a Monte Carlo method is used.
void rooms(int N, int*** D, int iter, int** ret, int processes);

// Implementation in which Simulated Annealing is used.
void roomsSA(int N, int*** D, int iter, double temp, double value, int** ret, int processes);

// Implementation in which a Greedy method is used.
void roomsGreedy(int N, int*** D, int** ret, int processes);

#endif