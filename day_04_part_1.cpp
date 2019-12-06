#include <iostream>
#include <vector>
using namespace std;

void getDigits(vector<int>& digits, int number) {
    int divider = 100000;

    while (divider != 0) {
        digits.push_back(number / divider);
        number %= divider;
        divider /= 10;
    }
}

void possiblePasswords(vector<int>& passwords, int lb, int up) {
    for (int i = lb; i < up; i++) {
        // It is a six-digit number
        if (to_string(i).size() != 6)
            continue;

        vector<int> digits;
        getDigits(digits, i);

        // Two adjacent digits are the same (like 22 in 122345)
        // Going from left to right, the digits never decrease;
        // they only ever increase or stay the same (like 111123 or 135679)
        bool eqDigits = false;
        bool increase = false;
        for (int j = 0; j < digits.size() - 1; ++j) {
            if (digits[j] == digits[j+1])
                eqDigits = true;
            if (digits[j] > digits[j+1])
                increase = true;
        }

        if (eqDigits && !increase)
            passwords.push_back(i);
    }
}

int main()
{
    vector<int> passwords;

    possiblePasswords(passwords, 136760, 595730);
    cout << passwords.size() << endl;

    return 0;
}