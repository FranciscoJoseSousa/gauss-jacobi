#ifndef _JACOBI_H_
#define _JACOBI_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define e 0.01
#define seed 1
#define Ne 1

void jacovipar_new(int N,int T);
void jacoviseq_new(int N);
#endif
