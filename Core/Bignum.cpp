#include "Bignum.h"

Bignum::Bignum(string val) {
    setVal(val);
}

void Bignum::setVal(string val) {
    nums.clear();
    sign = 1;
    if (val.at(0) == '-') {
        sign = -1;
        val = val.substr(1);
    }

    for (int i = val.length() - 1; i >= 0; i--) {
        int thisNum = char2int(val.at(i));
        nums.push_back(thisNum);
    }

}

string Bignum::toString() {
    string val;
    if (sign == -1)
        val += "-";
    for (int i = nums.size() - 1; i >= 0; i--)
        val += int2string(nums[i]);
    return val;
}

/**
 * only add the nums, without setting the sign
 */
Bignum Bignum::numsAdd(const vector<int> &a, const vector<int> &b) {
    Bignum result;
    int up = 0;
    int minLen = a.size() < b.size() ? a.size() : b.size();

    for (int i = 0; i < minLen; i++) {
        int thisSum = a[i] + b[i] + up;
        if (thisSum >= 10) {
            thisSum -= 10;
            up = 1;
        } else up = 0;
        result.nums.push_back(thisSum);
    }

    const vector<int> *longer = a.size() > b.size() ? &a : &b; // copy by reference
    for (int i = minLen; i < longer->size(); i++) {
        int thisNum = longer->at(i) + up;
        if (thisNum >= 10) {
            thisNum -= 10;
            up = 1;
        } else up = 0;
        result.nums.push_back(thisNum);
    }

    if (up != 0)
        result.nums.push_back(up);

    return result;
}

int Bignum::numsCompare(const vector<int> &a, const vector<int> &b) {
    if (a.size() > b.size())
        return 1;
    else if (a.size() < b.size())
        return -1;
    else {
        for (int i = a.size() - 1; i >= 0; i--) {
            if (a[i] > b[i])
                return 1;
            else if (a[i] < b[i])
                return -1;
        }
        return 0; // finish the comparison of all elements, ensuring equal
    }
}

Bignum Bignum::numsMinus(const vector<int> &a, const vector<int> &b) {
    Bignum result;
    const vector<int> *longer, *shorter;
    int down = 0;
    if (numsCompare(a, b) >= 0) {
        longer = &a;
        shorter = &b;
        result.sign = 1;
    } else {
        longer = &b;
        shorter = &a;
        result.sign = -1;
    }

    for (int i = 0; i < shorter->size(); i++) {
        int thisDiff = longer->at(i) - shorter->at(i) - down;
        if (thisDiff < 0) {
            thisDiff += 10;
            down = 1;
        } else down = 0;
        result.nums.push_back(thisDiff);
    }

    for (int i = shorter->size(); i < longer->size(); i++) {
        int thisNum = longer->at(i) - down;
        if (thisNum < 0) {
            thisNum += 10;
            down = 1;
        } else down = 0;
        result.nums.push_back(thisNum);
    }

    while (result.nums.size() > 1 && result.nums[result.nums.size() - 1] == 0)
        result.nums.pop_back();

    return result;
}

Bignum operator+(const Bignum &a, const Bignum &b) {
    Bignum result;
    if (a.sign == b.sign) {
        result = Bignum::numsAdd(a.nums, b.nums); // has not set the sign
        result.sign = a.sign;
    } else {
        result = Bignum::numsMinus(a.nums, b.nums); // has set the local sign
        result.sign *= (a.sign == 1 ? 1 : -1);
    }
    return result;
}

Bignum operator-(const Bignum &a, const Bignum &b) {
    Bignum result;
    if (a.sign != b.sign) {
        result = Bignum::numsAdd(a.nums, b.nums); // has not set the sign
        result.sign = a.sign;
    } else {
        result = Bignum::numsMinus(a.nums, b.nums); // has set the local sign
        result.sign *= (a.sign == 1 ? 1 : -1);
    }
    return result;
}

Bignum operator*(const Bignum &a, const Bignum &b) {
    Bignum result("0");
    vector<Bignum> products;
    for (int i = 0; i < a.nums.size(); i++) {
        Bignum product;
        product.sign = 1;

        int flag = 0; // <= 8
        for (int j = 0; j < b.nums.size(); j++) {
            int thisProduct = a.nums[i] * b.nums[j] + flag; // <= 9 * 9 + 8
            if (thisProduct >= 10) {
                flag = thisProduct / 10;
                thisProduct %= 10;
            } else flag = 0;
            product.nums.push_back(thisProduct);
        }

        if (flag != 0)
            product.nums.push_back(flag);

        product.nums.insert(product.nums.begin(), i, 0); // add i 0s in the lower end

        products.push_back(product);
    }

    for (auto &product : products)
        result += product;

    result.sign = a.sign * b.sign;

    return result;
}

Bignum operator*(const int &a, const Bignum &b) {
    Bignum A(Bignum::int2string(a));
    return A * b;
}

Bignum operator*(const Bignum &a, const int &b) {
    return b * a;
}

Bignum &operator+=(Bignum &a, const Bignum &b) {
    a = a + b;
    return a;
}

string Bignum::int2string(int i) {
    stringstream ss;
    ss << i;
    string s;
    ss >> s;
    return s;
}

int Bignum::char2int(char c) {
    if (c <= 47 || c >= 58)
        exit(-1);
    return c - 48;
}
