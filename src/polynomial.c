#include "polynomial.h"

/* Calculate the value of plynomial at a given value. */
double calPoly(polynomial *p, double x) {
    double result = 0;
    for (int i = 0; i < p->n; i++) {
        result += p->coeff[i] * pow(x, p->degree[i]);
    }
    return result;
}

/* Parse a polynomial and return a array of decree and coefficients, and the length of those array len */
int parsePolynomial(char *eq, double *degree, double *coeff, int *len) {
    int n = strlen(eq);
    char eq2[1000] = {0};
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 && j == 0 && eq[i] == 'x') {
            eq2[j++] = '1';
            i--;
        } else if ((eq[i] == 'x') && (i == n - 1 || eq[i + 1] == '+' || eq[i + 1] == '-')) {
            eq2[j++] = eq[i];
            eq2[j++] = '^';
            eq2[j++] = '1';
        } else if ((eq[i] == '+' || eq[i] == '-') && (eq[i + 1] == 'x')) {
            eq2[j++] = eq[i];
            eq2[j++] = '1';
        } else {
            eq2[j++] = eq[i];
        }
    }
    // eq2[j] == '\0';
    int j0 = 0, j1 = 0;
    char *f = eq2, *s;
    for (int i = 0; i < strlen(eq2);) {
        coeff[j0++] = strtod(f, &s);
        i += s - f;
        if (eq2[i] == 'x') {
            i += 2;
            f = eq2 + i;
            degree[j1++] = strtod(f, &s);
            i += s - f;
            f = eq2 + i;
        } else {
            degree[j1++] = 0;
            f = s;
        }
    }
    *len = j1;
    // printf("\ndegree:: ");
    // for (int i = 0; i < j0; i++)
    //     printf("%lf ", degree[i]);
    // printf("\ncoeff :: ");
    // for (int i = 0; i < j1; i++)
    //     printf("%lf ", coeff[i]);

    return 0;
}

char *displayPolynomial(polynomial *p) {
    char *ch = malloc(sizeof(char) * 1000);
    char *ch1 = malloc(sizeof(char) * 1000);
    int i;
    for (i = 0; i < p->n; i++) {
        if (p->coeff[i] == 0) {
            continue;
        } else if (p->coeff[i] == 1) {
            if (p->degree[i] == 1) {
                sprintf(ch, "(x)+");
            } else {
                sprintf(ch, "(x^%.2lf)+", p->degree[i]);
            }
        } else if (p->degree[i] == 0) {
            sprintf(ch, "(%.2lf)+", p->coeff[i]);
        } else if (p->degree[i] == 1) {
            sprintf(ch, "(%.2lfx)+", p->coeff[i]);
        }
        else {
            sprintf(ch, "(%.2lfx^%.2lf)+", p->coeff[i], p->degree[i]);
        }
        strcat(ch1, ch);
    }
    ch1[strlen(ch1)-1] = '\0';
    return ch1;
}