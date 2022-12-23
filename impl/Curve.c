#include"../lib/Curve.h"


Curve initCurve(int numPoints, int range[])
{
    Curve curve;
    curve.numPoints = numPoints;
    curve.range[0] = range[0];
    curve.range[1] = range[1];
    curve.points = (Point *)malloc(numPoints * sizeof(Point));
    return curve;
}

void storeCurveData(Curve curve)
{
    FILE *filePtr = openFile(CURVE_DATA_FILE, "w");
    for (int i = 0; i <= curve.numPoints; i++)
    {
        fprintf(filePtr, "%.2f,%.2f\n", curve.points[i].x, curve.points[i].y);
    }

    fclose(filePtr);
}

void storeMultyCurvesData(Curve curves[], int numCurves)
{
    FILE *filePtr = openFile(CURVE_DATA_FILE, "w");
    int i, j, numPoints = curves[0].numPoints;
    for (j = 0; j <= numPoints; j++)
    {
        for (i = 0; i < numCurves; i++)
        {
            fprintf(filePtr, "%.2f,%.2f,", curves[i].points[j].x, curves[i].points[j].y);
        }
        fprintf(filePtr, "\n");
    }

    fclose(filePtr);
}