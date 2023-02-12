#include "lagrange.hpp"
#include <limits>

/*Module: X22I050: Création Numérique & Algorithme numérique */
/* TP3: Polynôme d'interpolation de Lagrange*/
/* Anh NGUYEN - Aymen EL OUAGOUTI, Groupe 485 */

/*la fonction qui retourne le tableau de points équidistants xvals*/
/* Précondtion: l'intervalle [a,b] doit être valide, ça veut dire que a < b,
le nomdre de point d'interpolation doit supérieur de 0 parce que c'est aussi la taille de tableau xvals */
/*
 * @param a la borne inférieur de l'intervalle
 * @param b la borne supérieur de l'intervalle
 * @param n la nombre de point d'interpolation
 * @returns tableau de n+1 points équidistances.
 */
double *xvals(double a, double b, int n)
{
    double *x = new double[n + 1];

    for (int i = 0; i < n + 1; i++)
    {
        x[i] = (a + i * (b - a)) / n;

        if (x[i] == 0.0)
        {
            x[i] = numeric_limits<double>::min();
        }
    }
    return x;
}

// prend en entrée un pointeur de fonction (pfunc) et un tableau de xvals, et retourne un tableau de yvals//
// qui sont les valeurs de la fonction pfunc () aux points xvals.//
/* Précondtion: le nomdre de point d'interpolation doit supérieur de 0*/
/*
 * @param (*pfunc)(double) pointer de fonction qui doonée
 * @param *xvals tableau de points équidistances
 * @param n la taille du tableau(doit être egal à n dans xvals)
 */

double *yvals(double (*pfunc)(double), double *xvals, int n)
{
    double *y = new double[n];
    for (int i = 0; i < n; i++)
    {
        y[i] = (*pfunc)(xvals[i]);
    }
    return y;
}

// La fonction baseLagrange () calcule la base de Lagrange l_i (xn)
// pour un point d'interpolation donné i.
/*Précondition: le nombre de N doit être égal à la taille du tableau de xvals et yvals
la valeur de i doit être compris dans l'intervalle [0, N-1]
la valeur de x doit être type double pour calculer le base de Lagrange.*/
double baseLagrange(double *xvals, int N, int i, double x)
{
    double res;
    int j;
    res = 1.0;
    for (j = 0; j < N; j++)
    {
        if (j != i)
        {
            res = res * (x - xvals[j]) / (xvals[i] - xvals[j]);
        }
    }
    return res;
}

// La fonction lagrangeAppro () utilise la base de Lagrange
// pour calculer l'approximation de Lagrange en un point x donné.
/*Précondition: toutes les préconstions précédentes sont valide*/
/*
 * @param x point évalué
 * @param n degré du polynome
 * @param xvals tableau de points equidistants
 * @param yvals tableau d'images de xvals */
double lagrangeAppro(double x, int n, double *xvals, double *yvals)
{
    double l;
    l = 0.0;
    for (int i = 0; i < n; i++)
    {
        l = l + yvals[i] * baseLagrange(xvals, n, i, x);
    }
    return l;
}
