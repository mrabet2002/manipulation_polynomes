#include <stdio.h>
#include "lib/NewtonRaphson.h"
#include "lib/Polynomial.h"

#define NUM_CURVES 3

int main()
{
    //
    // --------------------------------------------------------------------------------------
    // ---------------------------- Declaration des variables -------------------------------
    // --------------------------------------------------------------------------------------
    //
    Polynomial p1, p2, sum;
    Curve curves[NUM_CURVES];
    int range[2], courbe, op;
    double x, *p1Approximation;
    Data data;
    data.separator = ",";
    data.src1 = CURVE_DATA_FILE;
    //
    // --------------------------------------------------------------------------------------
    // -------------------------------- Programme de test -----------------------------------
    // --------------------------------------------------------------------------------------
    //
    // Creation des polynomes ---------------------------------------------------------------
    // initPolynomial(&p1);
    // addNode(createNode((Monome){3, 2}), &p1);
    // addNode(createNode((Monome){-5, 1}), &p1);
    // addNode(createNode((Monome){6, 0}), &p1);
    // Le polynomial p2
    // initPolynomial(&p2);
    // addNode(createNode((Monome){1, 3}), &p2);
    // addNode(createNode((Monome){-1, 1}), &p2);
    // addNode(createNode((Monome){2, 0}), &p2);
    //
    // Affichage des polynomes -------------------------------------------------------------
    // printf("p1(x) = ");
    // printPolynomial(p1);
    // printf("\n");
    // printf("p2(x) = ");
    // printPolynomial(p2);
    // printf("\n");
    //
    // La somme de deux polynome ----------------------------------------------------------
    // sum = sumPolynomial(p1, p2);
    // printf("P(x) + Q(x) = ");
    // printPolynomial(sum);
    // printf("\n");
    //
    // Calcule d'une approximation --------------------------------------------------------
    // p1Approximation = polynomialRootApprox(p1);
    //
    // if (p1Approximation)
    // {
    //     double approximation = *p1Approximation;
    //     printf("l'approximation de p1(x) = 0 est : %lf\t", approximation);
    // }
    // else
    //     printf("l'approximation de p2(x) = 0 est non trouver\n");
    // --------------------------------------------------------------------------------------
    //
    // --------------------------------------------------------------------------------------
    // ------------------------------- Programme principal ----------------------------------
    // --------------------------------------------------------------------------------------
    //
    initPolynomial(&p2);
    initPolynomial(&sum);
    p1 = scanPoly();
    printf("Choisire l'opperation que vous voulez appliquer sur ce polynome :\n");
    printf("(1) Afficher \n");
    printf("(2) Evaluer la valeur \n");
    printf("(3) Changer le signe \n");
    printf("(4) Calculer le derivee \n");
    printf("(5) Faire l'addition avec un autre polynome \n");
    printf("(6) Faire la soustraction avec un autre polynome \n");
    printf("(7) Faire la comparaison avec un autre polynome \n");
    printf("(8) Tracer la courbe \n");
    printf("(9) Calculer l'approximation \n");
    printf("(0) Quitter le programme \n");
    while (TRUE)
    {
        printf("Tapper le numero de l'opperation : ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("P(x) = ");
            printPolynomial(p1);
            printf("\n");
            break;
        case 2:
            printf("Qelle est la valeur de x ? ");
            scanf("%lf", &x);
            printf("P(%.2f) = %.2f\n", x, calulate(p1, x));
            break;
        case 3:
            printf("P(x) apres changement de signe : \n");
            printf("P(x) = ");
            changePolynomialSign(&p1);
            printPolynomial(p1);
            printf("\n");
            break;
        case 4:
            printf("P'(x) = ");
            printPolynomial(polynomialDerivative(p1));
            printf("\n");
            break;
        case 5:
            printf("Saisire le deuxieme polynome :\n");
            p2 = scanPoly();
            printf("P(X) + Q(x) = ");
            sum = sumPolynomial(p1, p2);
            printPolynomial(sum);
            printf("\n");
            break;
        case 6:
            printf("Saisire le deuxieme polynome :\n");
            p2 = scanPoly();
            printf("P(X) - Q(x) = ");
            printPolynomial(substractPolynomial(p1, p2));
            printf("\n");
            break;
        case 7:
            printf("Saisire le deuxieme polynome :\n");
            p2 = scanPoly();
            printf("Les deux polynome sont %s", comparePolynomial(p1, p2)?"egaux":"differents");
            printf("\n");
            break;
        case 8:
            printf("Qulle courbe voulez vous tracer ?\n");
            printf("Courbe de P(x) (1)\n");
            printf("Courbe de Q(x) (2)\n");
            printf("Courbe de P(X) + Q(x) (3)\n");
            printf("Les trois courbes dans le maime graphe (4)\n");
            scanf("%d", &courbe);
            printf("Donnez l'interval [a,b] \n");
            printf("a = ");
            scanf("%d", &range[0]);
            printf("b = ");
            scanf("%d", &range[1]);
            Chart chart = __constChart("Polynome", "X", "P(X)", NULL, "15", "2", 1, data);
            switch (courbe)
            {
            case 1:
                curves[0] = computePolynomial(p1, range);
                storeCurveData(curves[0]);
                drawChart(chart);
                break;
            case 2:
                if (p2.head != NULL)
                {
                    curves[0] = computePolynomial(p2, range);
                    storeCurveData(curves[0]);
                    drawChart(chart);
                }
                break;
            case 3:
                if (sum.head != NULL)
                {
                    curves[0] = computePolynomial(sum, range);
                    storeCurveData(curves[0]);
                    drawChart(chart);
                }
                break;
            case 4:

                if (p2.head && sum.head)
                {
                    curves[0] = computePolynomial(p1, range);
                    curves[1] = computePolynomial(p2, range);
                    curves[2] = computePolynomial(sum, range);
                    storeMultyCurvesData(curves, 3);
                    chart.numCurves = 3;
                    drawChart(chart);
                }
                break;

            default:
                break;
            }
            printf("\n\n");
            break;
        case 9:
            p1Approximation = polynomialRootApprox(p1);

            if (p1Approximation)
            {
                double approximation = *p1Approximation;
                printf("l'approximation de P(x) = 0 est : %lf\t", approximation);
            }
            else
                printf("l'approximation de P(x) = 0 est non trouver\n");
            break;

        default:
            return 0;
        }
    }

    return 0;
}
