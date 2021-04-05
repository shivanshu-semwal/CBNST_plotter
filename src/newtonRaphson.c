#include "newtonRaphson.h"

double newtonRaphson(polynomial *p, polynomial *p0, double xn){
    
    double xn0;
    xn0 = xn;

    // calculating tolerance
    int noDigits = 4;
    double t = 0.5 * pow(10.0, -noDigits);

    printf("x_i\t| f(x_i)\n");
    while (1) {
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

double newtonRaphson1(polynomial *p, polynomial *p0){
    
    double xn, xn0;

    // calculating tolerance
    int noDigits = 4;
    double t = 0.5 * pow(10.0, -noDigits);

    // input
    printf("Enter initial approximation:: ");
    scanf("%lf", &xn);
    xn0 = xn;

    printf("x_i\t| f(x_i)\n");
    while (1) {
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