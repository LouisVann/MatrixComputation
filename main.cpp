#include "MatrixCalculator.h"

// todo
#include "Core/Bignum.h"
#include "Core/Matrix.h"
#include <iostream>


int main() {
    MatrixCalculator matrixCalculator;
    matrixCalculator.calculate("../matrix.in", "../expression.in", "../result.out");

//    Bignum a;
//    a.setVal("8");
//    Bignum b;
//    b.setVal("-6");
//    cout << (a*b).toString() << endl;
//    cout << a.toString() << endl;
    return 0;
}