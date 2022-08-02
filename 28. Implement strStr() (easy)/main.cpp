#include <cassert>
#include <iostream>
#include <string>

class Solution {
public:
    static int strStr(std::string& haystack, std::string& needle) {
        int i = 0;
        while (i < haystack.size()) {
            if (haystack[i] != needle[0] && i + needle.size() >= haystack.size())
                break;
            if (haystack[i] != needle[0]) {
                i++;
                continue;
            }
            // haystack[i] == needle[0]
            if (needle.size() == 1)
                return i;
            for (int ni = 1; ni < needle.size(); ni++) {
                int hi = i + ni;
                if (haystack[hi] == needle[ni]) {
                    if (ni == needle.size() - 1)
                        return i;
                } else { // haystack[hi] != needle[ni]
                    break;
                }
            }
            i++;
        }

        return -1;
    }
};

int main() {
    std::string haystack1 = "hello";
    std::string needle1 = "ll";
    assert(Solution::strStr(haystack1, needle1) == 2);

    std::string haystack2 = "aaaaa";
    std::string needle2 = "bba";
    assert(Solution::strStr(haystack2, needle2) == -1);

    std::string haystack3 = "abcabc";
    std::string needle3 = "abcd";
    assert(Solution::strStr(haystack3, needle3) == -1);

    std::string haystack4 = "abcabcdabcd";
    std::string needle4 = "abcd";
    assert(Solution::strStr(haystack4, needle4) == 3);

    std::string haystack5 = "a";
    std::string needle5 = "a";
    assert(Solution::strStr(haystack5, needle5) == 0);
}
