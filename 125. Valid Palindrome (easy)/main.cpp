#include <cassert>
#include <string>

class Solution {
public:
    static bool isPalindrome(std::string s) {
        uint32_t l_idx = 0;
        uint32_t r_idx = s.size() - 1;
        while (l_idx < r_idx) {
            if (!isalnum(s[l_idx])) {
                ++l_idx;
                continue;
            }
            if (!isalnum(s[r_idx])) {
                --r_idx;
                continue;
            }
            if (tolower(s[l_idx]) != tolower(s[r_idx]))
                return false;
            ++l_idx;
            --r_idx;
        }

        return true;
    }
};

int main() {
    assert(Solution::isPalindrome("A man, a plan, a canal: Panama"));
    assert(Solution::isPalindrome(" "));
    assert(Solution::isPalindrome("race a car") == false);

    return 0;
}
