#ifndef PROJECT1_CALCULATOR_H
#define PROJECT1_CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//enum for the type of two numbers:
enum numType {unknown = 0, type_integer = 1, type_double= 2, sciNum = 3, NaN = 4};

typedef int type;
//struct for the input:
typedef struct input {
    char* input_str;    //The original string input by user.
    short str_length;
    short count_point;  //To count how many points are in the string.
    short count_e;      //To count how many 'e's are in the string.
    double val;
    type  input_type;   //To show the type of the input.
} input;

bool initStruct(input* number);
bool isOperatorValid (const char* ch);
bool isInputNumber (input* number);
void inputToNonSciNum (input* number);
void numberAdd(input* number, double* result);
void numberSubtract(input* number, double* result);
void numberMultiply(input* number, double* result);
void numberDivide(input* number, double* result);
double* numberCalculation (input* number, const char* operator);
int setOutputPrecision (char* str_value, double value);

#endif //PROJECT1_CALCULATOR_H