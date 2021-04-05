#include "newtonRaphson.h"

double newtonRaphson(polynomial *p, polynomial *p0, double xn) {

    double xn0;
    xn0 = xn;
    double slope_lim = 0.00001;
    // calculating tolerance
    int noDigits = 4;
    double t = 0.5 * pow(10.0, -noDigits);

    printf("x_i\t| f(x_i)\n");
    while (1) {
        if (fabs(calPoly(p0, xn0)) < slope_lim) {
            printf("Slope is too small. (stuck at some local maxima or minima) Stoping execution....");
            exit(0);
        }
        xn = xn0 - (calPoly(p, xn0) / calPoly(p0, xn0));
        printf("%lf\t| %lf\n", xn, calPoly(p, xn));
        if (calPoly(p, xn) == 0) {
            printf("Result :: %lf", xn);
            break;
        } else if (fabs(xn0 - xn) < t) {
            printf("Result:: %lf within %lf tolerance.", xn, t);
            break;
        }
        xn0 = xn;
    }
    return xn;
}