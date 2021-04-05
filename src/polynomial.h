#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #ifndef POLY_H_

#define POLY_H_
typedef struct polynomial {
    int n;
    double *coeff;
    double *degree;
} polynomial;

double calPoly(polynomial *p, double x);
int parsePolynomial(char *eq, double *degree, double *coeff, int *len);
char *displayPolynomial(polynomial *p);
polynomial *getDerivative(polynomial *p);
// #endif