#ifndef MATRIXCOMPUTATION_BIGNUM_H
#define MATRIXCOMPUTATION_BIGNUM_H

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Bignum {
public:
    Bignum() = default;
    explicit Bignum(string val);

    void setVal(string val);
    string toString();

    friend Bignum operator+(const Bignum &a, const Bignum &b);
    friend Bignum operator-(const Bignum &a, const Bignum &b);
    friend Bignum operator*(const Bignum &a, const Bignum &b);
    friend Bignum operator*(const int &a, const Bignum &b);
    friend Bignum operator*(const Bignum &b, const int &a);
    friend Bignum& operator+=(Bignum &a, const Bignum &b);

private:
    vector<int> nums; // from low to high, ranging from 0 to 9
    int sign; // 1 or -1

    // inner toolkit functions
    static string int2string(int i);
    static int char2int(char c);

    static Bignum numsAdd(const vector<int> &a, const vector<int> &b);
    static Bignum numsMinus(const vector<int> &a, const vector<int> &b);
    static int numsCompare(const vector<int> &a, const vector<int> &b);
};




#endif //MATRIXCOMPUTATION_BIGNUM_H
