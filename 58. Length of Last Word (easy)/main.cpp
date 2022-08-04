#include <cassert>
#include <string>

class Solution {
public:
    static int lengthOfLastWord(const std::string& s) {
        int last_ch_i = (int) s.size();
        for (int i = (int) s.size() - 1; i >= 0; --i) {
            if (s[i] == ' ') {
                if (last_ch_i == s.size())
                    continue;
                else
                    return last_ch_i - i;
            } else { // non-space character
                if (last_ch_i == s.size())
                    last_ch_i = i;
                if (i == 0)
                    return last_ch_i + 1;
            }
        }

        return (int) s.size();
    }
};

int main() {
    const std::string s1 = "Hello World";
    assert(Solution::lengthOfLastWord(s1) == 5);

    const std::string s2 = "   fly me   to   the moon  ";
    assert(Solution::lengthOfLastWord(s2) == 4);

    const std::string s3 = "luffy is still joyboy";
    assert(Solution::lengthOfLastWord(s3) == 6);

    const std::string s4 = "a";
    assert(Solution::lengthOfLastWord(s4) == 1);

    const std::string s5 = "aaa";
    assert(Solution::lengthOfLastWord(s5) == 3);

    const std::string s6 = "aaa  ";
    assert(Solution::lengthOfLastWord(s6) == 3);

    const std::string s7 = "a  ";
    assert(Solution::lengthOfLastWord(s7) == 1);

    const std::string s8 = "   a";
    assert(Solution::lengthOfLastWord(s8) == 1);

    const std::string s9 = "   aaa";
    assert(Solution::lengthOfLastWord(s9) == 3);

    return 0;
}
