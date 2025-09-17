#include <cassert>
#include <string>
#include <vector>

class Solution {
public:
    static std::string intToRoman(int num) {
        std::string res;

        // 1000
        res += getRoman1000(num / 1000);
        num = num % 1000;

        // 100
        res += getRoman100(num / 100);
        num = num % 100;

        // 10
        res += getRoman10(num / 10);
        num = num % 10;

        // 1
        res += getRoman1(num);

        return res;
    }

    static std::string getRoman1000(int digit) {
        if (digit >= 1) {
            std::string res(digit, 'M');
            return res;
        }

        return "";
    }

    static std::string getRoman100(int digit) {
        if (digit == 9) {
            return "CM";
        } else if (digit > 5 && digit <= 8) {
            std::string res(digit - 5, 'C');
            return "D" + res;
        } else if (digit == 5) {
            return "D";
        } else if (digit == 4) {
            return "CD";
        } else if (digit >= 1 && digit <= 3) {
            std::string res(digit, 'C');
            return res;
        }

        return "";
    }

    static std::string getRoman10(int digit) {
        if (digit == 9) {
            return "XC";
        } else if (digit > 5 && digit <= 8) {
            std::string res(digit - 5, 'X');
            return "L" + res;
        } else if (digit == 5) {
            return "L";
        } else if (digit == 4) {
            return "XL";
        } else if (digit >= 1 && digit <= 3) {
            std::string res(digit, 'X');
            return res;
        }

        return "";
    }

    static std::string getRoman1(int digit) {
        if (digit == 9) {
            return "IX";
        } else if (digit > 5 && digit <= 8) {
            std::string res(digit - 5, 'I');
            return "V" + res;
        } else if (digit == 5) {
            return "V";
        } else if (digit == 4) {
            return "IV";
        } else if (digit >= 1 && digit <= 3) {
            std::string res(digit, 'I');
            return res;
        }

        return "";
    }
};

int main() {
    assert(Solution::intToRoman(3) == "III");
    assert(Solution::intToRoman(58) == "LVIII");
    assert(Solution::intToRoman(1994) == "MCMXCIV");

    return 0;
}
