#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <math.h>

// #include "matrix.hpp"
#include "util.hpp"
#include "lagrange.hpp"

/*Module: X22I050: Création Numérique & Algorithme numérique */
/* TP3: Polynôme d'interpolation de Lagrange*/
/* Anh NGUYEN - Aymen EL OUAGOUTI, Groupe 485 */

#define BOUND_A 0.0
#define BOUND_B 1.0

using namespace std;

/*Définire de fonctipon donnée dans le sujet de TP3*/
double solution(double x)
{
    return x / sqrt(x);
}

int main(int argc, char **argv)
{
    int nb_inter_pts = 100;
    int nb_echant_pts = 10000;

    double *tabx = xvals(BOUND_A, BOUND_B, nb_inter_pts - 1);
    double *taby = yvals(&solution, tabx, nb_inter_pts);
    cout << "la valeur de f(x): " << solution(0.55) << endl;

    cout << "solution de Lagrange x/sqrt(x) en 0.55 est " << lagrangeAppro(0.55, nb_inter_pts, tabx, taby) << endl;

    /*créer un tableau de tab_x_echant qui permet de calculer des valeurs d'échantillonées*/
    double *tab_x_echant = new double[nb_echant_pts];

    double distAB = fabs(BOUND_B - BOUND_A);
    for (int i = 0; i < nb_echant_pts; i++)
    {
        tab_x_echant[i] = BOUND_A + i * distAB / nb_echant_pts;
    }

    double *tab_y_echant = new double[nb_echant_pts];

    for (int i = 0; i < nb_echant_pts; i++)
    {
        tab_y_echant[i] = lagrangeAppro(tab_x_echant[i], nb_inter_pts, tabx, taby);
    }

    /*créer un tableau qui calculer les valeurs de la fonction f(x)*/
    double *fonction = yvals(&solution, tab_x_echant, nb_echant_pts);
    plot(tab_x_echant, fonction, nb_echant_pts, "f(x) = x/sqrt(x)", "actualFunction");

    plot(tab_x_echant, tab_y_echant, nb_echant_pts, "lagrange de = x/sqrt(x)", "polynôme de Lagrange en x = 0.55");

    double *errorRel = (double *)calloc(nb_echant_pts, sizeof(double));

    estimateRelError(errorRel, tabx, taby, nb_inter_pts, &solution, BOUND_A, BOUND_B, nb_echant_pts);

    double maxRelError = getMax(errorRel, nb_echant_pts);
    cout << "max relative error: " << maxRelError << endl;
    plot(tab_x_echant, errorRel, nb_echant_pts, "Relative approximation error for f(x) with Lagrange", "testPlotFuncRelError");

    double *errorAbs = (double *)calloc(nb_echant_pts, sizeof(double));

    estimateAbsError(errorAbs, tabx, taby, nb_inter_pts, &solution, BOUND_A, BOUND_B, nb_echant_pts);

    double maxAbsError = getMax(errorAbs, nb_echant_pts);
    cout << "max absolute error: " << maxAbsError << endl;
    plot(tab_x_echant, errorAbs, nb_echant_pts, "Relative approximation error for f(x) with Lagrange", "testPlotFuncAbsError");

    free(tabx); // Style C pour désallocation, à la place de delete[] en C++
    free(taby);
    free(errorRel);
    free(errorAbs);
    return 0;
}