#ifndef MATRIXCOMPUTATION_MATRIX_H
#define MATRIXCOMPUTATION_MATRIX_H

#include "Bignum.h"

#define COL_NUM 3
#define ROW_NUM 3

using namespace std;

class Matrix {
public:
    Matrix() = default;
    Bignum matrix[ROW_NUM][COL_NUM];
    string toString();

    friend Matrix operator+(const Matrix &a, const Matrix &b);
    friend Matrix operator-(const Matrix &a, const Matrix &b);
    friend Matrix operator*(const Matrix &a, const Matrix &b);
    friend Matrix operator*(const Matrix &a, const int &b);
    friend Matrix operator*(const int &a, const Matrix &b);
    friend Matrix operator~(const Matrix &a);
    friend Matrix& operator+=(Matrix &a, const Matrix &b);
    friend Matrix& operator-=(Matrix &a, const Matrix &b);

};


#endif //MATRIXCOMPUTATION_MATRIX_H
