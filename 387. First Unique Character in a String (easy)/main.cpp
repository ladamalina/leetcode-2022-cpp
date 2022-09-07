#include <cassert>
#include <string>
#include <vector>

class Solution {
public:
    static int firstUniqChar(std::string& s) {
        std::vector<bool> non_unique_chars(26, false);
        std::vector<int> unique_chars_to_idx(26, -1); //  unique charts code to first index
        int s_size = static_cast<int>(s.size());
        for (int i = 0; i < s_size; ++i) {
            uint8_t ch_code = (uint8_t) s[i] - 48 - 49;

            if (non_unique_chars[ch_code])
                continue;
            if (unique_chars_to_idx[ch_code] > -1) {
                unique_chars_to_idx[ch_code] = -1;
                non_unique_chars[ch_code] = true;
            } else
                unique_chars_to_idx[ch_code] = i;
        }
        int min_idx = s_size;
        for (const auto& idx : unique_chars_to_idx)
            if (idx > -1 && idx < min_idx)
                min_idx = idx;
        if (min_idx == s_size)
            min_idx = -1;

        return min_idx;
    }
};

int main() {
    std::string s1 = "leetcode";
    assert(Solution::firstUniqChar(s1) == 0);

    std::string s2 = "loveleetcode";
    assert(Solution::firstUniqChar(s2) == 2);

    std::string s3 = "aabb";
    assert(Solution::firstUniqChar(s3) == -1);

    std::string s4;
    assert(Solution::firstUniqChar(s4) == -1);

    std::string s5 = "a";
    assert(Solution::firstUniqChar(s5) == 0);

    std::string s6 = "aadadaad";
    assert(Solution::firstUniqChar(s6) == -1);
}
