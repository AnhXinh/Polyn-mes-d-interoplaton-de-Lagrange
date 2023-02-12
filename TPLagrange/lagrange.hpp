#include <iostream>
#include "util.hpp"
using namespace std;



double *xvals(double a, double b, int n);
double *yvals( double (*pfunc)(double), double *xvals, int n );
double baseLagrange(double *xvals, int N, int i, double x);
double lagrangeAppro( double x, int n, double *xvals, double *yvals);
