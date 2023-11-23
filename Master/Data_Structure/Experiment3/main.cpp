#include <iostream>
#include <ctime>
#include "mytuple.h"
using namespace TUPLE;
using namespace std;

int main() {
    cout << fixed;
    cout.precision(2);
    time_t t;
    srand((unsigned int) time(&t));

    cout << "<Create Two Matrix>" << endl;
    string matrixA, matrixB;
    cout << "Name the matrixA: ";   cin >> matrixA;
    cout << endl;
    cout << "Name the matrixB: ";   cin >> matrixB;
    cout << endl;
    Mymatrix A;
    Mytuple tupleA;
    Mymatrix B;
    Mytuple tupleB;

    cout << '<' << matrixA << ">" << endl;
    A.getRandomMatrix();
    A.storeInTuple(tupleA);

    cout << '<' << matrixB << ">" << endl;
    B.getRandomMatrix();
    B.storeInTuple(tupleB);

    tupleB = 3 * tupleB - tupleA;

    cout << '<' << matrixA << ">" << endl;
    Mytuple::transpose(tupleA);
    A.showMatrix(tupleA);
    cout << '<' << matrixB << ">" << endl;
    B.showMatrix(tupleB);

    return 0;
}
