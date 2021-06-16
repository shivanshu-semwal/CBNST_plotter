#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/polynomial.h"

// include other files

#include "src/bisection.h"
#include "src/newtonRaphson.h"
#include "src/plotter.h"
#include "src/regulaFalsi.h"

int main() {

    printf("Enter the function::\n");

    char eq[1000] = {0}, *lf;
    fgets(eq, sizeof(eq), stdin);
    if ((lf = strchr(eq, '\n')) != NULL) *lf = '\0';

    double degree[100] = {0.0}, coeff[100] = {0.0};
    int len = 0;
    if (parsePolynomial(eq, degree, coeff, &len) != 0) {
        printf("\nError in polynomial.....\n");
        exit(1);
    }

    polynomial *p = malloc(sizeof(polynomial));
    p->n = len;
    p->degree = degree;
    p->coeff = coeff;

    printf("\n Polynomial:: ||f(x) = %s|| \n", displayPolynomial(p));

    // menu
    printf("\n=======================\n");
    printf("1. Bisection\n");
    printf("2. Regula falsi\n");
    printf("3. Newton's Raphsons\n");
    printf("0. Exit\n");
    printf("Enter your choice:: ");

    int ch, c;
    scanf("%d", &ch);

    switch (ch) {
    case 1: {
        double x0 = 0, x1 = 0;
        // input range till valid range is found
        while (x0 == x1 || calPoly(p, x0) * calPoly(p, x1) > 0) {
            printf("\nEnter a valid range:: ");
            scanf("%lf %lf", &x0, &x1);
        }
        double root = bisection(p, x0, x1);
        printf("\nRoot is:: %lf\n", root);
        makePlot(p, x0, x1, root, "my_image.png");
        break;
    }
    case 2: {
        double x0 = 0, x1 = 0;
        // input range till valid range is found
        while (x0 == x1 || calPoly(p, x0) * calPoly(p, x1) > 0) {
            printf("\nEnter a valid range:: ");
            scanf("%lf %lf", &x0, &x1);
        }
        double root = regulaFalsi(p, x0, x1);
        printf("\nRoot is:: %lf\n", root);
        makePlot(p, x0, x1, root, "my_image.png");
        break;
    }
    case 3: {
        double x0;
        printf("\nEnter the initial guess:: ");
        scanf("%lf", &x0);

        polynomial *p1 = getDerivative(p);
        printf("\nDerivative:: ||f'(x) = %s||\n", displayPolynomial(p1));

        double root = newtonRaphson(p, p1, x0);
        printf("\nRoot:: %lf\n", root);
        double start = ((x0 <= root) ? x0 : root) - 1;
        double end = ((x0 >= root) ? x0 : root) + 1;
        makePlot(p, start, end, root, "my_image.png");
        free(p1);
        break;
    }
    default:
        break;
    }

    free(p);
    return 0;
}