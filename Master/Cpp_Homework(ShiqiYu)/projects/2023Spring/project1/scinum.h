#ifndef PROJECT1_SCINUM_H
#define PROJECT1_SCINUM_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "calculator.h"

typedef struct sciNum {
    double base;
    double power;
} mySciNum;

double getBase(double value);
double getPower(double value);
void resetSciNum(mySciNum* sci_ary);
void getSciNum(input* number, mySciNum* sci_ary);
void exponentMatching(mySciNum* sci_ary);
mySciNum* sciAdd(mySciNum* sci_ary);
mySciNum* sciSubtract(mySciNum* sci_ary);
mySciNum* sciMultiply(mySciNum* sci_ary);
mySciNum* sciDivide(mySciNum* sci_ary);
mySciNum* sciCalculation(mySciNum* sci_ary, const char* operator);

#endif //PROJECT1_SCINUM_H