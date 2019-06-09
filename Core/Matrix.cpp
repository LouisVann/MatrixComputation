#include "Matrix.h"

string Matrix::toString() {
    string matrixString;
    for (int i = 0; i < ROW_NUM; ++i) {
        for (int j = 0; j < COL_NUM; ++j) {
            matrixString += matrix[i][j].toString();
            matrixString += " ";
        }
        matrixString += "\n";
    }
    return matrixString;
}

Matrix operator+(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++)
            c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
    }
    return c;
}

Matrix operator-(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++)
            c.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
    }
    return c;
}

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            c.matrix[i][j] = Bignum("0");
            for (int k = 0; k < COL_NUM; k++)
                c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
        }
    }
    return c;
}

Matrix operator*(const Matrix &a, const int &b) {
    Matrix c;
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++)
            c.matrix[i][j] = a.matrix[i][j] * b;
    }
    return c;
}

Matrix operator*(const int &a, const Matrix &b) {
    return b * a;
}

Matrix operator~(const Matrix &a) {
    Matrix b;
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++)
            b.matrix[j][i] = a.matrix[i][j];
    }
    return b;
}

Matrix &operator+=(Matrix &a, const Matrix &b) {
    a = a + b;
    return a;
}

Matrix &operator-=(Matrix &a, const Matrix &b) {
    a = a - b;
    return a;
}
