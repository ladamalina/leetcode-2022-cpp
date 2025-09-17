#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    static int lengthOfLongestSubstring(std::string& s) {
        if (s.empty()) {
            return 0;
        }

        int longest_seq = 0;
        int current_seq = 0;
        std::unordered_map<char, int> chars_to_idx;
        int begin_idx = 0;
        int i = 0;
        while (i < s.size()) {
            if (chars_to_idx.find(s[i]) == chars_to_idx.end()) { // Meet unique
                chars_to_idx[s[i]] = i;
                current_seq++;
            } else { // Meet double
                if (current_seq > longest_seq)
                    longest_seq = current_seq;
                int double_char_first_idx = chars_to_idx[s[i]];
                for (int j = begin_idx; j <= double_char_first_idx; ++j)
                    chars_to_idx.erase(s[j]);
                begin_idx = double_char_first_idx + 1;
                chars_to_idx[s[i]] = i;
                current_seq = i - double_char_first_idx;
            }
            i++;
        }
        if (current_seq > longest_seq)
            longest_seq = current_seq;

        return longest_seq;
    }
};

int main() {
    std::string s1 = "abcabcbb";
    assert(Solution::lengthOfLongestSubstring(s1) == 3);

    std::string s2 = "bbbbb";
    assert(Solution::lengthOfLongestSubstring(s2) == 1);

    std::string s3 = "pwwkew";
    assert(Solution::lengthOfLongestSubstring(s3) == 3);

    std::string s4 = "abcdefghijklmnopqrstuvwxyz";
    assert(Solution::lengthOfLongestSubstring(s4) == 26);
}
