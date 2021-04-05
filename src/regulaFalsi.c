#include "regulaFalsi.h"

double regulaFalsi(polynomial *p, double x0, double x1) {
    double c = 0;

    // calculating tolerance
    int noDigits = 4;
    double t = 0.5 * pow(10.0, -noDigits);
    double x_prev = 0;
    printf("x0\t| c\t| x1\t| f(c)\n");
    while (1) {
        x_prev = c;
        c = (x0 * calPoly(p, x1) - x1 * calPoly(p, x0)) / (calPoly(p, x1) - calPoly(p, x0));
        printf("%lf\t| %lf\t| %lf\t| %lf\n", x0, c, x1, calPoly(p, c));
        if (calPoly(p, c) == 0) {
            printf("Result is :: %lf", c);
            break;
        } else if (calPoly(p, x0) * calPoly(p, c) < 0) {
            x1 = c;
        } else {
            x0 = c;
        }
        if (fabs(c - x_prev) < t) {
            printf("Result is :: %lf  within %lf tolerance", c, t);
            break;
        }
    }

    return c;
}