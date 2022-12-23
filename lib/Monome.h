#include <stdio.h>
#include <stdlib.h>

#ifndef MONOME_H

#define MONOME_H
#define MONOME_MAX_SIZE 50

typedef enum boolean
{
    FALSE,
    TRUE
} boolean;

typedef struct Monome
{
    double coef;
    int pow;
} Monome;

Monome createMonome(double, int);
void printMonome(Monome);
Monome scanMonome();
boolean monomesAreEqual(Monome, Monome);
Monome monomeDerivative(Monome);
char *monomeToString(Monome);

Monome createMonome(double coef, int pow)
{
    Monome monome;
    monome.coef = coef;
    monome.pow = pow;
    return monome;
}

void printMonome(Monome m)
{
    printf("%.2fX^%d ", m.coef, m.pow);
}

Monome scanMonome()
{
    int pow;
    double coef;

    printf("Coefficient : ");
    scanf("%lf", &coef);
    printf("Puissance : ");
    scanf("%d", &pow);
    return createMonome(coef, pow);
}

boolean monomesAreEqual(Monome a, Monome b)
{
    return ((a.coef == b.coef) && (a.pow == b.pow));
}

Monome monomeDerivative(Monome monome)
{
    monome.coef *= monome.pow;
    monome.pow--;
    return monome;
}

char *monomeToString(Monome monome){
    char *mStr = (char*)malloc(MONOME_MAX_SIZE*sizeof(char));
    sprintf(mStr, "%.2f*x**%d", monome.coef, monome.pow);
    return mStr;
}

#endif