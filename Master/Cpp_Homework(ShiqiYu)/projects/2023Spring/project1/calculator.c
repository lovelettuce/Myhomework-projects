#include "calculator.h"

//Initialize two inputs.
bool initStruct(input* number) {
    int i = 0;
    while (i < 2) {
        //General input: 64+1bit(65 * 1 byte) + space + 64+1bit(65* 1 byte) + '\0'
        number[i].input_str = (char*)malloc( 65 * sizeof(char));
        if (!number[i].input_str) {
            return false;
        }
        number[i].str_length = 0;
        number[i].count_point = 0;
        number[i].count_e = 0;
        number[i].val = 0.0;
        number[i].input_type = unknown;
        i++;
    }
    return true;
}

/*
 *      Judge whether the input is a number or not,
 *      and then analyze the type of the number.
 */

bool isOperatorValid (const char* ch) {
    if (*ch == '+' || *ch == '-' ||
        *ch == '*' || *ch == '/')
        return true;
    else
        return false;
}

bool isInputNumber (input* number) {
    int i = 0;
    while (i < 2) {
        char* p = number[i].input_str;
        int position_e = 0;
        bool isEScanned = false;

        while (*p != '\0') {
            number[i].str_length++;
            if (*p != 'e' && !isEScanned)
                position_e++;
            if (number[i].str_length == 1 || number[i].str_length == position_e + 1) {
                if (*p == '+' || *p == '-') {
                    p++;
                    continue;
                }
            }

            if (*p >= '0' && *p <= '9') {
                p++;
                continue;
            }
            else if (*p == '.') {
                if (number[i].input_type != sciNum)
                    number[i].input_type = type_double;
                number[i].count_point++;
            }
            else if (*p == 'e') {
                isEScanned = true;
                if (number[i].str_length == 1) {
                    number[i].input_type = NaN;
                    printf("The input cannot be interpreted to numbers.\n");
                    return false;
                } else {
                    position_e++;
                    number[i].input_type = sciNum;
                    number[i].count_e++;
                }
            }
            else {
                number[i].input_type = NaN;
                printf("The input cannot be interpreted to numbers.\n");
                return false;
            }
            p++;
        }
        if (number[i].count_e == 0) {
            if (number[i].count_point == 0) {
                number[i].input_type = type_integer;
            }
            if (number[i].count_point > 1) {
                number[i].input_type = NaN;
                printf("The input cannot be interpreted to numbers.\n");
                return false;
            }
        }
        if (number[i].count_e == 1) {
            if (position_e == number[i].str_length) {
                number[i].input_type = NaN;
                printf("The input cannot be interpreted to numbers.\n");
                return false;
            }
            if (number[i].count_point == 2) {
                p = number[i].input_str;
                short count_point_again = 0;
                while (*p != 'e') {
                    if (*p == '.')  count_point_again++;
                    p++;
                }
                if (count_point_again != 1) {
                    number[i].input_type = NaN;
                    printf("The input cannot be interpreted to numbers.\n");
                    return false;
                }
            }
        }
        i++;
    }
    return true;
}

void inputToNonSciNum (input* number) {
    int i = 0;
    while (i < 2) {
        if (number[i].input_type == sciNum) {
            i++;
            continue;
        }
        if (number[i].input_type == type_integer) {
            number[i].val = atoi(number[i].input_str);
        }
        if (number[i].input_type == type_double) {
            number[i].val = atof(number[i].input_str);
        }
        i++;
    }
}

void numberAdd(input* number, double* result) {
    if (number[0].input_type == sciNum || number[1].input_type == sciNum) return;
    else {
        double sum = number[0].val + number[1].val;
        if ((sum > 0 && (sum > 2147483647 || sum < 0.000001)) ||
            (sum < 0 && (sum < -2147483647 || sum > -0.000001)))
        {
            //Convert two numbers to sciNum.
            number[0].input_type = sciNum, number[1].input_type = sciNum;
            //Do add operation with sciNum-version.
        }
        else
            *result = sum;
    }
}

void numberSubtract(input* number, double* result) {
    if (number[0].input_type == sciNum || number[1].input_type == sciNum) return;
    else {
        double sub = number[0].val - number[1].val;
        if ((sub > 0 && (sub > 2147483647 || sub < 0.000001)) ||
            (sub < 0 && (sub < -2147483647 || sub > 0.000001)))
        {
            //Convert two numbers to sciNum.
            number[0].input_type = sciNum, number[1].input_type = sciNum;
            //Do sub operation with sciNum-version.
        }
        else
            *result = sub;
    }
}

void numberMultiply(input* number, double* result) {
    if (number[0].input_type == sciNum || number[1].input_type == sciNum) return;
    else {
        double mul = number[0].val * number[1].val;
        if ((mul > 0 && (mul > 2147483647 || mul < 0.000001)) ||
            (mul < 0 && (mul < -2147483647 || mul > 0.000001)))
        {
            //Convert two numbers to sciNum.
            number[0].input_type = sciNum, number[1].input_type = sciNum;
            //Do multiply operation with sciNum-version.
        }
        else
            *result = mul;
    }
}

void numberDivide(input* number, double* result) {
    //Condition: number[1].val != 0
    if (number[0].input_type == sciNum || number[1].input_type == sciNum) return;
    else {
        double div = number[0].val / number[1].val;
        if ((div > 0 && (div > 2147483647 || div < 0.000001)) ||
            (div < 0 && (div < -2147483647 || div > 0.000001)))
        {
            //Convert two numbers to sciNum.
            number[0].input_type = sciNum, number[1].input_type = sciNum;
            //Do divide operation with sciNum-version.
        }
        else
            *result = div;
    }
}

double* numberCalculation (input* number, const char* operator) {
    if (number[0].input_type == sciNum || number[1].input_type == sciNum) {
        //do sciNum calculation
    }
    double* result = (double*) malloc(sizeof(double));
    if (number[0].input_type != sciNum && number[1].input_type != sciNum) {
        switch(*operator) {
            case '+' :  numberAdd(number, result);      break;
            case '-' :  numberSubtract(number, result); break;
            case '*' :  numberMultiply(number, result); break;
            case '/' :
            {
                if(number[1].val == 0){
                    result = NULL;
                    printf("A number cannot be divided by zero.\n");
                }
                else
                    numberDivide(number, result);
            }   break;

            default  :  break;
        }
    }
    return result;
}

int setOutputPrecision (char* str_value, double value) {
    sprintf(str_value, "%lf", value);
    char* p = str_value;
    bool isEnd = false;
    bool isAfterPoint = false;
    int position = 0, i = 0;
    while (*p != '\0') {
        if (isAfterPoint) {
            if (*p == '0') {
                if (!isEnd)
                    position = i;
                isEnd = true;
            }
            else
                isEnd = false;
            i++;
        }
        if (*p == '.')
            isAfterPoint = true;
        p++;
    }
    return position;
}