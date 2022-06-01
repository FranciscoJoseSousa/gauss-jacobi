#ifndef _JACOBI_H_
#define _JACOBI_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define e 0.01
#define seed 1
#define Ne 1

double jacovipar(int N,int T);
double jacobiseq(int N);
void teste();

#endif
