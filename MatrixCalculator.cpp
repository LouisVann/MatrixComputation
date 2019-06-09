#include <fstream>
#include <iostream>
#include <stack>
#include "MatrixCalculator.h"

void MatrixCalculator::calculate(string matrix_path, string expression_path, string result_path) {
    readMatrices(matrix_path);
    readExpressions(expression_path);

    ofstream fo(result_path);
    for (string &expression : expressions) {
        Matrix result = computeOneExpression(expression);
        fo << result.toString();
    }
    fo.close();
}

void MatrixCalculator::readMatrices(const string &matrix_path) {
    ifstream in;
    in.open(matrix_path);
    if (in.fail())
        cout << "Failed in reading matrices file." << endl;

    int numOfMatrices;
    in >> numOfMatrices;
    for (int i = 0; i < numOfMatrices; i++) {
        // for each matrix
        string name;
        in >> name;
        Matrix thisMatrix;

        for (int j = 0; j < ROW_NUM; j++) {
            for (int k = 0; k < COL_NUM; k++) {
                string val;
                in >> val;
                thisMatrix.matrix[j][k].setVal(val);
            }
        }

        matrixMappings[name] = thisMatrix;
    }

    in.close();
}

void MatrixCalculator::readExpressions(const string &expression_path) {
    ifstream in;
    in.open(expression_path);
    if (in.fail())
        cout << "Failed in reading expressions file." << endl;

    string expression;
    while (in >> expression) {
        expressions.push_back(expression);
    }

    in.close();
}

Matrix MatrixCalculator::computeOneExpression(string expression) {
    // postfix
    stack<string> s1, s2;
    int len = expression.length();
    int i = 0;
    while (i < len) {
        string str = "";
        if (expression.at(i) == '+' || expression.at(i) == '-' ||
            expression.at(i) == '*' || expression.at(i) == '~') {
            str += expression.at(i);

            if (expression.at(0) && (i == 0 || !isCharacter(expression.at(i - 1))) &&
                (i + 1 < len && isNumber(expression.at(i + 1)))) {
                i++;
                while (i < len && isNumber(expression.at(i))) {
                    str += expression.at(i);
                    i++;
                }
                s2.push(str);
            } else {
                if (i + 1 < len && (str == "+" || str == "-") && expression.at(i + 1) == '=') {
                    str += expression.at(i + 1);
                    i++;
                }

                while (!s1.empty() && getPriority(str) <= getPriority(s1.top())) {
                    s2.push(s1.top());
                    s1.pop();
                }
                s1.push(str);
                i++;
            }
        } else if (isCharacter(expression.at(i))) {
            while (i < len && isCharacter(expression.at(i))) {
                str += expression.at(i);
                i++;
            }
            s2.push(str);
        } else if (isNumber(expression.at(i))) {
            while (i < len && isNumber(expression.at(i))) {
                str += expression.at(i);
                i++;
            }
            s2.push(str);
        }
    }
    ////////////////////////////////////////////////////////////////////////////////
    while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
    }
    while (!s2.empty()) { // 再把s2的内容依次放入s1，因为此时s2是逆波兰式的倒序。
        s1.push(s2.top());
        s2.pop();
    }

    // 利用s1来运算
    while (!s1.empty()) {
        if (s1.top() == "+=") {
            string str1 = s2.top();
            s2.pop();
            string str2 = s2.top();
            s2.pop();
            matrixMappings[str2] += matrixMappings[str1];
            s2.push(str2);
        } else if (s1.top() == "-=") {
            string str1 = s2.top();
            s2.pop();
            string str2 = s2.top();
            s2.pop();
            matrixMappings[str2] -= matrixMappings[str1];
            s2.push(str2);
        } else if (s1.top() == "~") {
            string str = "~" + s2.top();
            matrixMappings[str] = ~matrixMappings[s2.top()];
            s2.pop();
            s2.push(str);
        } else if (s1.top() == "+") {
            string str1 = s2.top();
            s2.pop();
            string str2 = s2.top();
            s2.pop();
            string str;

            str += str2; // 被ide推荐这么写。。
            str += "+";
            str += str1;

            matrixMappings[str] = matrixMappings[str1] + matrixMappings[str2];
            s2.push(str);
        } else if (s1.top() == "-") {
            string str1 = s2.top();
            s2.pop();
            string str2 = s2.top();
            s2.pop();
            string str;

            str += str2;
            str += "-";
            str += str1;

            matrixMappings[str] = matrixMappings[str2] - matrixMappings[str1];
            s2.push(str);
        } else if (s1.top() == "*") {
            string str1 = s2.top();
            s2.pop();
            string str2 = s2.top();
            s2.pop();
            string str;

            str += str2;
            str += "*";
            str += str1;

            if (isAllNumber(str1)) { // 记一次偷懒引发的惨案
                int a = atoi(str1.c_str());
                matrixMappings[str] = a * matrixMappings[str2];
            } else if (isAllNumber(str2)) {
                int a = atoi(str2.c_str());
                matrixMappings[str] = a * matrixMappings[str1];
            } else
                matrixMappings[str] = matrixMappings[str2] * matrixMappings[str1];

            s2.push(str);
        } else {
            s2.push(s1.top());
        }
        s1.pop();
    }
    return matrixMappings[s2.top()];


}

int MatrixCalculator::getPriority(string s) {
    if (s == "+=" || s == "-=")
        return 0;
    else if (s == "+" || s == "-")
        return 1;
    else if (s == "*")
        return 2;
    else if (s == "~")
        return 3;
    else
        return -1;
}

bool MatrixCalculator::isCharacter(char i) {
    return (i >= 65 && i <= 90) || (i >= 97 && i <= 122);
}

bool MatrixCalculator::isNumber(char i) {
    return i >= 48 && i <= 59;
}

bool MatrixCalculator::isAllNumber(string s) {
    int slen = s.length();
    int i = 0;
    if (s.at(i) == '-')
        i++;
    else if (!isNumber(s.at(i)))
        return false;

    for (; i < slen; i++) {
        if (!isNumber(s.at(i)) || (i == 0 && s.at(i) == '-'))
            return false;
    }
    return true;
}