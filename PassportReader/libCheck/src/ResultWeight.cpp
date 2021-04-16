#include "ResultWeight.h"

int defaultWeight[14] = { 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
int CHN_E[14] = { 0, 8, 10, 5, 5, 5, 5, 5, 5, 10, 5, 5, 5, 5 };

int CalculateResult(int temp[14], int nation, int type)
{
    int* src = defaultWeight;
    if (nation == 32 && type == 7)
    {
        src = CHN_E;
    }

    int maxnum = 0;
    int sumnum = 0;
    for (int m = 0; m < 14; ++m)
    {
        if (temp[m] != 5)
            maxnum += src[m];
        if (temp[m] == 1)
            sumnum += src[m];
    }
    if (sumnum > maxnum * 0.8)
        return 1;
    else
        return 2;
}