#include <cassert>
#include <string>
#include <vector>

class Solution {
public:
    static int compareVersion(std::string& version1, std::string& version2) {
        uint16_t v1 = 0;
        uint16_t v2 = 0;
        uint16_t v1_next_idx = 0;
        uint16_t v2_next_idx = 0;
        while (v1_next_idx < version1.size() || v2_next_idx < version2.size()) {
            std::tie(v1, v1_next_idx) = getVersion(version1, v1_next_idx);
            std::tie(v2, v2_next_idx) = getVersion(version2, v2_next_idx);
            if (v1 < v2)
                return -1;
            if (v1 > v2)
                return 1;
        }
        return 0;
    }

    static std::pair<uint16_t, uint16_t> getVersion(const std::string& str, const size_t& begin_idx) {
        std::string v_str;
        for (size_t i = begin_idx; i < str.size(); ++i) {
            if (str[i] == '.')
                break;
            v_str += str[i];
        }
        if (v_str.empty())
            return {0, str.size()};
        else {
            uint16_t v = stoi(v_str);
            return {v, begin_idx + v_str.size() + 1};
        }
    }
};

int main() {
    std::string v1_1 = "1.01";
    std::string v1_2 = "1.001";
    assert(Solution::compareVersion(v1_1, v1_2) == 0);

    std::string v2_1 = "1.0";
    std::string v2_2 = "1.0.0";
    assert(Solution::compareVersion(v2_1, v2_2) == 0);

    std::string v3_1 = "0.1";
    std::string v3_2 = "1.1";
    assert(Solution::compareVersion(v3_1, v3_2) == -1);

    std::string v4_1 = "1.0.1";
    std::string v4_2 = "1";
    assert(Solution::compareVersion(v4_1, v4_2) == 1);

    return 0;
}
