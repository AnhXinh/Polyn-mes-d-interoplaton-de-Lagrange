#include "util.hpp"
#include <math.h>
#include "lagrange.hpp"
#include <cmath>

/*Module: X22I050: Création Numérique & Algorithme numérique */
/* TP3: Polynôme d'interpolation de Lagrange*/
/* Anh NGUYEN - Aymen EL OUAGOUTI, Groupe 485 */

/* This funciton evaluates a polynomial of degree polyDegree using Horner's method at the value x.
Attention, polyDegree is the degree of the polynomial, i.e. poly has polyDegree+1 elements.
*/
using namespace std;
double horner(const double *poly, uint64_t polyDegree, double x)
{
    double result = poly[polyDegree]; // Initialize result
    // cout << "horner" << endl;
    // cout << result << endl;
    //  Evaluate value of polynomial using Horner's method
    for (int i = polyDegree - 1; i >= 0; i--)
    {
        result = result * x + poly[i];
        // cout << result << endl;
    }
    // cout << result << endl;
    return result;
}

/*
Given a polynomial poly of degree polyDegree, described as an array of double-precision coefficients,
a pointer to a function func, and an interval [a;b], this function fills out the array errors
with the relative errors |func(x_i) - poly(x_i)|/|func(x_i)| for each sample point x_i in [a;b], where the number of samples is given as a parameter.
The array errors is assumed to be allocated outside the function.

This is a naive and rough estimation of the approximation error.
*/
void estimateRelError(double *error, double *xvals, double *yvals, int n, double func(double), double a, double b, uint64_t nSamples)
{
    double distAB = fabs(b - a);
    double xi;
    for (int i = 0; i < nSamples; i++)
    {
        xi = a + i * distAB / nSamples;
        if (xi == 0.0)
        {
            xi = numeric_limits<double>::min();
        }
        error[i] = fabs((*func)(xi)-lagrangeAppro(xi, n, xvals, yvals)) / fabs((*func)(xi));
    }
}

/*
The same as the above unction but with absolute error.

Question : can we merge these functions and parametrize them by the desired error type ? How ?
*/
void estimateAbsError(double *error, double *xvals, double *yvals, int n, double func(double), double a, double b, uint64_t nSamples)
{

    double distAB = fabs(b - a);
    double xi;
    for (int i = 0; i < nSamples; i++)
    {
        xi = a + i * distAB / nSamples;
        if (xi == 0.0)
        {
            xi = numeric_limits<double>::min();
        }
        error[i] = fabs((*func)(xi)-lagrangeAppro(xi, n, xvals, yvals));
    }
}

/* Given a n-element array of doubles, this function computes the maximum element. */
double getMax(const double *array, uint64_t n)
{
    double max = array[0];
    for (int i = 0; i < n; ++i)
    {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

/*
This function plots a function defined by N 2D points using the gnuplot software (http://www.gnuplot.info)

Inputs : an array of points along x-axis, an array of points along y-axis, the number of points (N<= the length og arrays),
        the title of the plot and a filename.

*/
void plot(double *xvals, double *yvals, uint64_t N, char *title, char *filename)
{
    char gnuplot_command1[1000] = {0};
    sprintf(gnuplot_command1, "set terminal postscript eps enhanced color solid colortext 9 font \",15\" \n  set output '%s.eps' \n set key left below \n set style data line \n plot \"%s\" title \"%s\" \n", filename, filename, title);

    FILE *temp = fopen(filename, "w");

    for (int i = 0; i < N; i++)
    {
        fprintf(temp, "%le %le \n", xvals[i], yvals[i]); // Write the data to a temporary file
    }
    fclose(temp);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "%s", gnuplot_command1);
    //  fclose(gnuplotPipe);
}
