#include <cassert>
#include <cmath>

class Solution {
public:
    static bool isPalindrome(const int& x) {
        if (x < 0) {
            return false;
        }
        if (x < 10) {
            return true;
        }
        if (x % 10 == 0) {
            return false;
        }
        const auto digits_num = uint8_t(log10(x) + 1);
        const uint8_t half_digits_num = digits_num / 2;
        uint32_t left_half;
        if (digits_num % 2 > 0) {
            left_half = uint32_t(x / pow(10, (half_digits_num+1)));
        } else {
            left_half = uint32_t(x / pow(10, half_digits_num));
        }
        uint32_t right_half = x % uint32_t(pow(10, half_digits_num));
        uint32_t reverted_right = 0;
        for (uint8_t i=0; i<half_digits_num; i++) {
            reverted_right += uint32_t(right_half % 10) * uint32_t(pow(10, (half_digits_num-i-1)));
            right_half = right_half / 10;
        }
        return left_half == reverted_right;
    }
};

int main() {
    assert(Solution::isPalindrome(123454321) == true);
    assert(Solution::isPalindrome(123455321) == false);
    assert(Solution::isPalindrome(1234554321) == true);
    assert(Solution::isPalindrome(1234564321) == false);
    assert(Solution::isPalindrome(121) == true);
    assert(Solution::isPalindrome(1) == true);
    assert(Solution::isPalindrome(77) == true);
    assert(Solution::isPalindrome(10) == false);
    assert(Solution::isPalindrome(-121) == false);
    assert(Solution::isPalindrome(0) == true);
    assert(Solution::isPalindrome(123) == false);
    assert(Solution::isPalindrome(120021) == true);
    assert(Solution::isPalindrome(1230321) == true);
    return 0;
}
