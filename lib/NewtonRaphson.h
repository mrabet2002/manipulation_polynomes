#include <math.h>
#include "Polynomial.h"

#ifndef NEWTONRAPHSON_H

#define NEWTONRAPHSON_H
#define EPSILON 1e-20
#define MAX_ITER 100

double *polynomialRootApprox(Polynomial);

double *polynomialRootApprox(Polynomial poly)
{
    Polynomial polyDeriv = polynomialDerivative(poly);
    double *approximation;
    if (polyDeriv.head != NULL)
    {
        double x[2] = {1, 1};
        int n = 1;
        double polyDerivVal, polyVal;
        do
        {
            x[0] = x[1];
            polyVal = calulate(poly, x[0]);
            // printf("k = %d\tx%d = %lf\tp(x%d) = %lf\n", n - 1, n - 1, x[0], n - 1, polyVal);
            polyDerivVal = calulate(polyDeriv, x[0]);
            if (polyDerivVal == 0)
            {
                approximation = NULL;
                break;
            }
            x[1] = x[0] - polyVal / polyDerivVal;
            n++;
        } while ((fabs(x[1] - x[0]) > EPSILON) && (n <= MAX_ITER));

        if (n > MAX_ITER)
            approximation = NULL;
        else
            approximation = &x[1];
        return approximation;
    }
    return NULL;
}

#endif