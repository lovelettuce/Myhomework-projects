#include "scinum.h"
double getBase(double value) {
    bool isNumNegative = false;
    if (value == 0) return 0;
    if (value < 0) {
        isNumNegative = true;
        value = -value;
    }
    if (value > 0) {
        while (!(value < 10 && value >= 1)) {
            if (value >= 10)
                value /= 10;
            if (value < 1)
                value *= 10;
        }
    }
    return isNumNegative ? -value : value;
}

double getPower(double value) {
    return log10(value / getBase(value));
}

void resetSciNum(mySciNum* sci_ary) {
    bool isNegativeChanged = false;
    if (sci_ary->base == 0)
        return;
    if (sci_ary->base < 0) {
        sci_ary->base = -sci_ary->base;
        isNegativeChanged = true;
    }
    if (sci_ary->base > 0) {
        while (!(sci_ary->base >= 1 && sci_ary->base < 10)) {
            if (sci_ary->base < 1) {
                sci_ary->base *= 10;
                sci_ary->power--;
            } else if (sci_ary->base >= 10) {
                sci_ary->base /= 10;
                sci_ary->power++;
            }
        }
        if (isNegativeChanged)
            sci_ary->base = -sci_ary->base;
    }
}

void getSciNum(input* number, mySciNum* sci_ary) {
    int i = 0;
    while (i < 2) {
        if (number[i].val != 0) {
            sci_ary[i].base = getBase(number[i].val);
            sci_ary[i].power = getPower(number[i].val);
        }
        else {
            //It's a big number.
            int j = 0;
            char* str_base = (char*) malloc(32 * sizeof(char));
            char* str_pow = (char*) malloc(32 * sizeof(char));
            char* ptr_base = str_base, *ptr_pow = str_pow;
            for (int k = 0; k < 32; k++) {
                ptr_base[k] = '\0';
                ptr_pow[k] = '\0';
            }

            char* p = number[i].input_str;
            while (*p != 'e') {
                p++;
                j++;
            }
            strncpy(str_base,number[i].input_str,j);

            p++;
            j = 0;
            char* start_pow = p;
            while(*p != '\0') {
                p++;
                j++;
            }
            strncpy(str_pow,  start_pow, j);
            sci_ary[i].base = atof(str_base);
            sci_ary[i].power = atof(str_pow);
        }
        i++;
    }
}

void exponentMatching(mySciNum* sci_ary) {
    if (sci_ary[0].power == sci_ary[1].power) return;
    double big_pow = sci_ary[0].power > sci_ary[1].power ?
                     sci_ary[0].power : sci_ary[1].power;
    int i = 0;
    while (i < 2) {
        if (big_pow == sci_ary[i].power) {
            i++;
            continue;
        }   //if;
        else {
            //this number has smaller power
            while (big_pow != sci_ary[i].power) {
                sci_ary[i].power++;
                sci_ary[i].base /= 10;
            }   //while; matching exponent succeed!
        }   //else;
        i++;
    }   //while;
}

mySciNum* sciAdd(mySciNum* sci_ary) {
    if (sci_ary[0].power != sci_ary[1].power)
        exponentMatching(sci_ary);  //Match the exponent.
    mySciNum* sci_result = (mySciNum*) malloc(sizeof(mySciNum));
    sci_result->power = sci_ary[0].power;
    sci_result->base = sci_ary[0].base + sci_ary[1].base;
    resetSciNum(sci_result);
    return sci_result;
}

mySciNum* sciSubtract(mySciNum* sci_ary) {
    if (sci_ary[0].power != sci_ary[1].power)
        exponentMatching(sci_ary);  //Match the exponent.
    mySciNum* sci_result = (mySciNum*) malloc(sizeof(mySciNum));
    sci_result->power = sci_ary[0].power;
    sci_result->base = sci_ary[0].base - sci_ary[1].base;
    resetSciNum(sci_result);
    return sci_result;
}

mySciNum* sciMultiply(mySciNum* sci_ary) {
    mySciNum* sci_result = (mySciNum*) malloc(sizeof(mySciNum));
    sci_result->base = sci_ary[0].base * sci_ary[1].base;
    sci_result->power = sci_ary[0].power + sci_ary[1].power;
    resetSciNum(sci_result);
    return sci_result;
}

mySciNum* sciDivide(mySciNum* sci_ary) {
    mySciNum* sci_result = (mySciNum*) malloc(sizeof(mySciNum));
    sci_result->base = sci_ary[0].base / sci_ary[1].base;
    sci_result->power = sci_ary[0].power - sci_ary[1].power;
    resetSciNum(sci_result);
    return sci_result;
}

mySciNum* sciCalculation(mySciNum* sci_ary, const char* operator) {
    mySciNum* sci_result = (mySciNum*) malloc(sizeof(mySciNum));
    switch(*operator) {
        case '+' :  sci_result = sciAdd(sci_ary);      break;
        case '-' :  sci_result = sciSubtract(sci_ary); break;
        case '*' :  sci_result = sciMultiply(sci_ary); break;
        case '/' :
        {
            if(sci_ary[1].base == 0){
                sci_result = NULL;
                printf("A number cannot be divided by zero.\n");
            }
            else
                sci_result = sciDivide(sci_ary);
        }   break;

        default  :  break;
    }
    return sci_result;
}