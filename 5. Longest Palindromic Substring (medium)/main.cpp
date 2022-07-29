#include <cassert>
#include <iostream>
#include <string>
#include <tuple>

class Solution {
public:
    Solution() = default;

    std::string longestPalindrome(std::string& s) {
        std::cout << "s = " << s << std::endl;
        int left_idx;
        int right_idx;

        for (int i = 0; i < s.size(); i++) {
            if (s.size() - i < longest_half_len)
                break;
            // Check if symbol may be middle of even palindrome
            if (i + 1 < s.size() && s[i] == s[i+1]) {
                std::tie(left_idx, right_idx) = Solution::getLongestPalindrome(s, i, i+1);
                updateLongestPalindrome(left_idx, right_idx);
            }
            // Any symbol may be middle of odd palindrome
            if (i - 1 >= 0 && i + 1 < s.size() && s[i-1] == s[i+1]) {
                std::tie(left_idx, right_idx) = Solution::getLongestPalindrome(s, i-1, i+1);
                updateLongestPalindrome(left_idx, right_idx);
            }
        }
        std::string longest_str(s.begin()+longest_left_idx, s.begin()+longest_right_idx+1);
        std::cout << "longest_str = " << longest_str << std::endl;

        return longest_str;
    }

private:
    int longest_left_idx = 0;
    int longest_right_idx = 0;
    int longest_len = 1;
    int longest_half_len = 0;

    static std::tuple<int, int> getLongestPalindrome(std::string& s, int mid_i_left, int mid_i_right) {
        do {
            mid_i_left--;
            mid_i_right++;
        } while (mid_i_left >= 0 && mid_i_right < s.size() && s[mid_i_left] == s[mid_i_right]);
        mid_i_left++;
        mid_i_right--;

        return std::make_tuple(mid_i_left, mid_i_right);
    }

    void updateLongestPalindrome(const int left_idx, const int right_idx) {
        int current_len = right_idx - left_idx + 1;
        if (current_len > longest_len) {
            longest_left_idx = left_idx;
            longest_right_idx = right_idx;
            longest_len = current_len;
            longest_half_len = longest_len / 2;
        }
    }
};

int main() {
    std::string s1 = "babad";
    assert(Solution().longestPalindrome(s1) == "bab");

    std::string s2 = "cbbd";
    assert(Solution().longestPalindrome(s2) == "bb");

    std::string s3 = "a";
    assert(Solution().longestPalindrome(s3) == "a");

    std::string s4 = "aaaa";
    assert(Solution().longestPalindrome(s4) == "aaaa");

    std::string s5 = "aaaaa";
    assert(Solution().longestPalindrome(s5) == "aaaaa");

    return 0;
}
