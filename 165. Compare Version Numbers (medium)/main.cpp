#include <cassert>
#include <string>
#include <vector>

class Solution {
    public:
    static int compareVersion(const std::string& version1, const std::string& version2) {
        auto v1 = 0, v1_e = 0;
        auto v2 = 0, v2_e = 0;
        while (v1_e < static_cast<int>(version1.size()) || v2_e < static_cast<int>(version2.size())) {
            std::tie(v1, v1_e) = getVersion(version1, v1_e);
            std::tie(v2, v2_e) = getVersion(version2, v2_e);
            if (v1 < v2) return -1;
            if (v1 > v2) return 1;
        }
        return 0;
    }

    static std::pair<int, int> getVersion(const std::string& s, int b) {
        auto e = b;
        while (e < static_cast<int>(s.size()) && s[e] != '.')
            ++e;
        if (b == e)
            return {0, s.size()};
        else {
            const auto v = std::stoi(s.substr(b, e-b));
            const auto v_e = e < static_cast<int>(s.size()) ? e+1 : e;
            return {v, v_e};
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
