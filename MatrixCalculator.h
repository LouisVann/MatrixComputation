#ifndef MATRIXCOMPUTATION_MATRIXCALCULATOR_H
#define MATRIXCOMPUTATION_MATRIXCALCULATOR_H

#include <map>
#include "Core/Matrix.h"

using namespace std;

class MatrixCalculator {
public:
    void calculate(string matrix_path, string expression_path, string result_path);

private:
    map<string, Matrix> matrixMappings;
    vector<string> expressions;

    void readMatrices(const string &matrix_path);
    void readExpressions(const string &expression_path);
    Matrix computeOneExpression(string expression);

    int getPriority(string s);
    bool isCharacter(char c);
    bool isNumber(char c);
    bool isAllNumber(string s);

};


#endif //MATRIXCOMPUTATION_MATRIXCALCULATOR_H
