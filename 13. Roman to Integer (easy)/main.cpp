#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    static int romanToInt(const std::string& s) {
        int res = 0;
        int i = static_cast<int>(s.size()) - 1;
        while (i >= 0) {
            int chVal = chToInt.at(s[i]);
            if (i == 0) {
                res += chVal;
                break;
            }
            if ((s[i] == 'V' || s[i] == 'X') && s[i-1] == 'I') {
                chVal -= 1;
                i--;
            }
            if ((s[i] == 'L' || s[i] == 'C') && s[i-1] == 'X') {
                chVal -= 10;
                i--;
            }
            if ((s[i] == 'D' || s[i] == 'M') && s[i-1] == 'C') {
                chVal -= 100;
                i--;
            }

            res += chVal;
            i--;
        }

        return res;
    }
private:
    static const std::unordered_map<char, int> chToInt;
};

const std::unordered_map<char, int> Solution::chToInt = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
};

int main() {
    const std::string s1 = "III";
    assert(Solution::romanToInt(s1) == 3);

    const std::string s2 = "LVIII";
    assert(Solution::romanToInt(s2) == 58);

    const std::string s3 = "MCMXCIV";
    assert(Solution::romanToInt(s3) == 1994);

    return 0;
}
