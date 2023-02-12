#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>



double  horner              (const double* poly, uint64_t polyDegree, double x) ;
void estimateRelError(double* error, double *xvals, double *yvals, int n, double func(double), double a, double b, uint64_t nSamples);
void estimateAbsError(double* error, double *xvals, double *yvals, int n, double func(double), double a, double b, uint64_t nSamples);
double  getMax              (const double* array, uint64_t n);
void    plot                (double *xvals, double *yvals, uint64_t N, char* title, char* filename);