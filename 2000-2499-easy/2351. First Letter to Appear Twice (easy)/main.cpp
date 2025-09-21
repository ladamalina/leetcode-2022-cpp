#include <cassert>
#include <unordered_set>
#include <string>
#include <vector>

class Solution {
public:
    static char repeatedCharacter(std::string& s) {
        std::vector<bool> seen_chars(26, false); // count of repeating
        for (int i = 0; i < s.size(); ++i) {
            uint8_t ch_code = (uint8_t) s[i] - 48 - 49;

            // meet char second time
            if (seen_chars[ch_code])
                return s[i];

            // meet char first time
            seen_chars[ch_code] = true;
        }

        return s[0];
    }
};

int main() {
    std::string s1 = "abccbaacz";
    assert(Solution::repeatedCharacter(s1) == 'c');

    std::string s2 = "abcdd";
    assert(Solution::repeatedCharacter(s2) == 'd');

    std::string s3 = "aabb";
    assert(Solution::repeatedCharacter(s3) == 'a');

    std::string s4 = "zz";
    assert(Solution::repeatedCharacter(s4) == 'z');
}
