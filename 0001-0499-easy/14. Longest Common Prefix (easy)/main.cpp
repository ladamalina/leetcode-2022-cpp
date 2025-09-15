#include <cassert>
#include <string>
#include <string_view>
#include <vector>

class Solution {
public:
    static bool isCharEq(const std::vector<std::string>& strs, const uint8_t& char_idx) {
        for (uint8_t str_idx = 0; str_idx < strs.size(); ++str_idx) {
            if (str_idx == 0) {
                continue;
            }
            if (char_idx >= strs[str_idx].size() || char_idx >= strs[str_idx-1].size()) {
                return false;
            }
            if (strs[str_idx][char_idx] != strs[str_idx-1][char_idx]) {
                return false;
            }
        }
        return true;
    }

    static std::string longestCommonPrefix(const std::vector<std::string>& strs) {
        if (strs.empty()) {
            return "";
        }
        if (strs.size() == 1) {
            return strs[0];
        }

        uint8_t char_idx = 0;
        while (true) {
            if (!Solution::isCharEq(strs, char_idx)) {
                break;
            }
            char_idx++;
        }

        return strs[0].substr(0,char_idx);
    }
};

int main() {
    assert(Solution::longestCommonPrefix({"flower", "flow", "flight"}) == "fl");
    assert(Solution::longestCommonPrefix({"flower", "flower", "flower"}) == "flower");
    assert(Solution::longestCommonPrefix({"flower", "flow", ""}).empty());
    assert(Solution::longestCommonPrefix({"", "flow", "flight"}).empty());
    assert(Solution::longestCommonPrefix({"", "flow"}).empty());
    assert(Solution::longestCommonPrefix({"dog", "racecar", "car"}).empty());
    assert(Solution::longestCommonPrefix({"racecar"}) == "racecar");
    assert(Solution::longestCommonPrefix({"", "", ""}).empty());
    assert(Solution::longestCommonPrefix({}).empty());
    return 0;
}
