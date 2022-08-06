#include <cctype>
#include <cmath>
#include <climits>
#include <string>
#include <vector>

class Solution {
public:
    static int myAtoi(const std::string& s) {
        bool sighIsFound = false;
        bool signIsPos = false;
        std::vector<uint8_t> digits = {};
        digits.reserve(11);
        int64_t res = 0;

        for (auto& ch : s) {
            if (!sighIsFound) {
                if (isdigit(ch)) {
                    sighIsFound = true;
                    signIsPos = true;
                    if (ch != '0')
                        digits.push_back(ch - '0');
                    continue;
                }
                if (ch == ' ')
                    continue;
                if (ch == '+') {
                    sighIsFound = true;
                    signIsPos = true;
                    continue;
                }
                if (ch == '-') {
                    sighIsFound = true;
                    signIsPos = false;
                    continue;
                }
                return 0;
            }
            // sighIsFound == true
            // collecting digits
            if (isdigit(ch)) {
                if (ch == '0' && digits.empty())
                    continue;
                digits.push_back(ch - '0');
                if (digits.size() >= 11)
                    break;
                continue;
            }
            break;
        }
        if (digits.empty())
            return 0;
        for (int i = 0; i < digits.size(); ++i) {
            if (signIsPos) {
                res += digits[digits.size() - i - 1] * (int64_t) std::pow(10, i);
                if (res > std::numeric_limits<int32_t>::max()) {
                    res = std::numeric_limits<int32_t>::max();
                    break;
                }
            } else {
                res -= digits[digits.size() - i - 1] * (int64_t) std::pow(10, i);
                if (res < std::numeric_limits<int32_t>::min()) {
                    res = std::numeric_limits<int32_t>::min();
                    break;
                }
            }
        }

        return (int32_t) res;
    }
};

int main() {
    assert(Solution::myAtoi("42") == 42);
    assert(Solution::myAtoi("0") == 0);
    assert(Solution::myAtoi("1") == 1);
    assert(Solution::myAtoi("-0") == 0);
    assert(Solution::myAtoi("-1") == -1);
    assert(Solution::myAtoi("   -42") == -42);
    assert(Solution::myAtoi("4193 with words") == 4193);
    assert(Solution::myAtoi("   -4193 with words") == -4193);
    assert(Solution::myAtoi("   -0 with words") == 0);
    assert(Solution::myAtoi("e   -47 with words") == 0);
    assert(Solution::myAtoi("   -4e7 with words") == -4);
    assert(Solution::myAtoi("   -4.7 with words") == -4);
    assert(Solution::myAtoi("   -47e with words") == -47);
    // > 2 147 483 648
    assert(Solution::myAtoi("9999999999999999999999999999999") == std::numeric_limits<int32_t>::max());
    assert(Solution::myAtoi("-9999999999999999999999999999999") == std::numeric_limits<int32_t>::min());
    assert(Solution::myAtoi("21474836460") == 2147483647);

    return 0;
}
