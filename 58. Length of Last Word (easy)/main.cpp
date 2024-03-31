#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
 public:
  static int lengthOfLastWord(const std::string& s) {
    const auto n = static_cast<int>(s.size());
    auto last_i = n;
    for (auto i = n; i>=0; --i) {
      if (s[i] == ' ') {
        if (last_i == n)
          continue;
        else
          return last_i - i;
      } else { // non-space character
        if (last_i == n)
          last_i = i;
        if (i == 0)
          return last_i + 1;
      }
    }
    return n;
  }
};

int main() {
  assert(Solution::lengthOfLastWord("Hello World"s) == 5);
  assert(Solution::lengthOfLastWord("   fly me   to   the moon  "s) == 4);
  assert(Solution::lengthOfLastWord("luffy is still joyboy"s) == 6);
  assert(Solution::lengthOfLastWord("aaa"s) == 3);
  assert(Solution::lengthOfLastWord("aaa  "s) == 3);
  assert(Solution::lengthOfLastWord("   aaa"s) == 3);
  assert(Solution::lengthOfLastWord("a"s) == 1);
  assert(Solution::lengthOfLastWord("a  "s) == 1);
  assert(Solution::lengthOfLastWord("   a"s) == 1);

  return 0;
}
