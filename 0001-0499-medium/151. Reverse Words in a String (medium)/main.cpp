#include <cassert>
#include <string>

class Solution {
public:
    static std::string reverseWords(std::string s) {
        std::string s2;
        s2.reserve(s.size());
        int word_begin_idx = s.size() - 1;
        int word_end_idx = s.size() - 1;
        for (int i = s.size()-1; i >= 0; --i) {
            if (s[i] == ' ') {
                if (i < s.size()-1 && s[i+1] != ' ') {
                    s2.insert(s2.end(), s.begin() + word_begin_idx, s.begin() + word_end_idx + 1);
                    s2 += ' ';
                }
            } else {
                word_begin_idx = i;
                if (i < s.size()-1 && s[i+1] == ' ') {
                    word_end_idx = i;
                }
            }
        }
        if (word_begin_idx == 0) {
            std::string word(s.begin() + word_begin_idx, s.begin() + word_end_idx + 1);
            s2 += word;
        }
        if (s2[s2.size() - 1] == ' ')
            s2.resize(s2.size()-1);

        return s2;
    }
};

int main() {
    assert(Solution::reverseWords("the sky is blue") == "blue is sky the");
    assert(Solution::reverseWords("  hello world  ") == "world hello");
    assert(Solution::reverseWords("a good   example") == "example good a");
    assert(Solution::reverseWords("a") == "a");
    assert(Solution::reverseWords("a  ") == "a");
    assert(Solution::reverseWords("  a") == "a");
    assert(Solution::reverseWords("  a  ") == "a");

    return 0;
}
