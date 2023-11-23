#include <stdio.h>
#include "calculator.h"
#include "scinum.h"

input number[2];
mySciNum sci_ary[2];

int main() {
    initStruct(number);
    char* operator = (char*) malloc(sizeof(char));
    double* result;
    mySciNum* sci_result;
    scanf("%s %c %s", number[0].input_str, operator, number[1].input_str);
    isOperatorValid(operator);
    char* result_1 = (char*) malloc(32 * sizeof(char));
    char* result_2 = (char*) malloc(32 * sizeof(char));
    int precision[2] = {0, 0};
    if (isInputNumber(number)) {
        if (number[0].input_type != sciNum && number[1].input_type != sciNum) {
            inputToNonSciNum(number);
            result = numberCalculation(number, operator);
            if (result) {
                precision[0] = setOutputPrecision(result_1, *result);
                printf("%s %c %s = %.*lf\n", number[0].input_str, *operator,
                       number[1].input_str, precision[0], *result);
            }
        }
        else {
            inputToNonSciNum(number);
            getSciNum(number, sci_ary);
            sci_result = sciCalculation(sci_ary, operator);
            if (sci_result) {
                if (sci_result->base != 0) {
                    precision[0] = setOutputPrecision(result_1, sci_result->base);
                    precision[1] = setOutputPrecision(result_2, sci_result->power);
                    printf("%s %c %s = %.*lfe%.*lf\n", number[0].input_str, *operator, number[1].input_str,
                           precision[0], sci_result->base, precision[1], sci_result->power);
                }
                else
                    printf("%s %c %s = 0\n",number[0].input_str, *operator, number[1].input_str);
            }
        }
    }
    return 0;
}