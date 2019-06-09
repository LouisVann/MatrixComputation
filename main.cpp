#include "MatrixCalculator.h"
#include <iostream>

int main() {
    MatrixCalculator matrixCalculator;
    matrixCalculator.calculate("../matrix.in", "../expression.in", "../result.out");
    return 0;
}