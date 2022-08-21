#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    static bool isIsomorphic(std::string s, std::string t) {
        std::vector<char> repl_s(128);
        std::vector<char> repl_t(128);
        for (size_t i = 0; i < s.size(); ++i) {
            uint8_t s_code = s[i] + 0;
            uint8_t t_code = t[i] + 0;
            if (!repl_s[s_code] && !repl_t[t_code]) {
                repl_s[s_code] = t[i];
                repl_t[t_code] = s[i];
                continue;
            }
            if (repl_s[s_code] && repl_t[t_code]) {
                if (repl_s[s_code] == t[i] && repl_t[t_code] == s[i])
                    continue;
                return false;
            }
            return false;
        }

        return true;
    }
};

int main() {
    assert(Solution::isIsomorphic("egg", "add"));
    assert(Solution::isIsomorphic("foo", "bar") == false);
    assert(Solution::isIsomorphic("paper", "title"));
    assert(Solution::isIsomorphic("foo", "aaa") == false);
    assert(Solution::isIsomorphic("qwertyuiop[]asdfghjkl;'\\zxcvbnm,./",
                                  "',.pyfgcrl/=aoeuidhtns-\\;qjkxbmwvz"));
    assert(Solution::isIsomorphic("13", "42"));

    return 0;
}
