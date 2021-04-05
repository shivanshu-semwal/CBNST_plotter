#include "plotter.h"

wchar_t * charTowchar_t(char *c){
    int n = strlen(c);
    wchar_t *ch = malloc(sizeof(wchar_t) * (n+40));
    swprintf(ch, n+20, L"f(x) = %hs", c);
    return ch;
}

void makePlot(polynomial *p, double x0, double x1, double root, char *name) {

    int n = 50;

    double x[n];
    double y[n];

    double max_y = DBL_MIN;
    double min_y = DBL_MAX;
    
    double h = (x1 - x0) / (double)n;
    for (int i = 0; i < n; i++) {
        x[i] = x0 + i * h;
        y[i] = calPoly(p, x[i]);
        if(y[i] > max_y) max_y = y[i];
        if(y[i] < min_y) min_y = y[i];
    }

    max_y++;
    min_y--;

    double xr[2] = {root, root};
    double yr[2] = {max_y, min_y};
    // printf("\n============================");
    // printf("\nValues for the plotter:: ");
    // printf("\n x\t y");
    // for (int i = 0; i < n; i++) {
    //     printf("\n%.2lf\t%.2lf", x[i], y[i]);
    // }
    // printf("\n============================");

    /* creating scatter plot of polynomial */
    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = x;
    series->xsLength = n;
    series->ys = y;
    series->ysLength = n;
    series->linearInterpolation = true;
    series->lineType = L"dashed";
    series->lineTypeLength = wcslen(series->lineType);
    series->lineThickness = 2;
    series->color = GetGray(0.3);

    /* creating straight line at the root */
    ScatterPlotSeries *series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = xr;
    series1->xsLength = 2;
    series1->ys = yr;
    series1->ysLength = 2;
    series1->linearInterpolation = true;
    series1->lineType = L"solid";
    series1->lineTypeLength = wcslen(series1->lineType);
    series1->lineThickness = 2;
    series1->color = CreateRGBColor(0, 1, 0);

    /* creating scatter plot settings  */
    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 600;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    char *c = displayPolynomial(p);
    wchar_t *cc = charTowchar_t(c);
    // settings->title = L"hello";
    settings->title = cc;
    settings->titleLength = wcslen(cc);
    settings->xLabel = L"X axis";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"Y axis";
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s[] = {series, series1};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 2;

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    DrawScatterPlotFromSettings(canvasReference, settings);

    size_t length;
    double *pngdata = ConvertToPNG(&length, canvasReference->image);
    WriteToFile(pngdata, length, name);
    DeleteImage(canvasReference->image);
}