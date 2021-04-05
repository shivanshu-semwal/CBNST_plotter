#include <math.h>
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

#include "src/polynomial.h"
#include "src/bisection.h"
#include "src/newtonRaphson.h"
#include "src/regulaFalsi.h"
#include "src/plotter.h"

int main() {

    printf("Enter the function::\n");

    char eq[1000] = {0}, *lf;
    fgets(eq, sizeof(eq), stdin);
    if ((lf = strchr(eq, '\n')) != NULL) *lf = '\0';

    double degree[100] = {0.0}, coeff[100] = {0.0};
    int len = 0;
    if (parsePolynomial(eq, degree, coeff, &len) != 0) {
        printf("\nError\n");
        exit(1);
    }

    polynomial *p = malloc(sizeof(polynomial));
    p->n = len;
    p->degree = degree;
    p->coeff = coeff;

    printf("\n %s \n", displayPolynomial(p));

    // menu
    printf("\n=======================\n");
    printf("1. Bisection\n");
    printf("2. Regula falsi\n");
    printf("3. Newton's Raphsons\n");
    printf("0. Exit\n");
    printf("Enter your choice:: ");

    int ch, c;
    scanf("%d", &ch);
    // while ((c = getchar()) != '\n' && c != EOF) {
    // }

    switch (ch) {
    case 1: {
        double x0 = 0, x1 = 0;
        // input range till valid range is found
        while (x0 == x1 || calPoly(p, x0) * calPoly(p, x1) > 0) {
            printf("\nEnter a valid range:: ");
            scanf("%lf %lf", &x0, &x1);
        }
        double root = bisection(p, x0, x1);
        printf("Root is:: %lf", root);
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
        printf("Root is:: %lf", root);
        makePlot(p, x0, x1, root, "my_image.png");
        break;
    }
    case 3: {
        double x0;
        printf("Enter the initial guess:: ");
        scanf("%lf", &x0);
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        printf("Enter the function derivative::\n");
        char eq1[1000] = {0};
        fgets(eq1, sizeof(eq1), stdin);
        if ((lf = strchr(eq1, '\n')) != NULL) *lf = '\0';

        double degree1[100] = {0.0}, coeff1[100] = {0.0};
        int len1 = 0;
        if (parsePolynomial(eq1, degree1, coeff1, &len1) != 0) {
            printf("\nError\n");
            exit(1);
        }
        polynomial *p1 = malloc(sizeof(polynomial));
        p1->n = len1;
        p1->degree = degree1;
        p1->coeff = coeff1;
        printf("Enter the initial guess:: ");
        scanf("%lf", &x0);
        // while ((c = getchar()) != '\n' && c != EOF) {
        // }
        double root = newtonRaphson(p,p1,x0);
        printf("Root:: %lf", root);
        break;
    }
    default:
        break;
    }
    return 0;
}