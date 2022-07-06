#ifndef POISSON_H
#define POISSON_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include "auxiliar.h"

int poissonJac(int N, double*** U, double*** W);

int poissonGS(int N, double*** W);

int poissonGSRBSeq(int N, double*** W);
int poissonGSRBPar(int N, double*** W);

int poissonSORRBSeq(int N, double*** W);
int poissonSORRBPar(int N, double*** W);

#endif