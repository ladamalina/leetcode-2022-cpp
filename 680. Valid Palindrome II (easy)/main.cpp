#include <cassert>
#include <string>

class Solution {
 public:
  static bool validPalindrome(const std::string& s) {
    if (s.size() <= 2) {
      return true;
    }
    return validPalindrome(s, 1, 0, static_cast<int>(s.size())-1);
  }
 private:
  static bool validPalindrome(const std::string& s, int most_ch_to_delete, int begin_i, int end_i) {
    while (begin_i <= end_i) {
      if (s[begin_i] == s[end_i]) {
        ++begin_i;
        --end_i;
        continue;
      }
      // s[begin_i] != s[end_i]
      if (most_ch_to_delete == 0) {
        return false;
      }
      return (validPalindrome(s, most_ch_to_delete-1, begin_i+1, end_i) ||
              validPalindrome(s, most_ch_to_delete-1, begin_i, end_i-1));
    }
    return true;
  }
};

int main() {
  assert(Solution::validPalindrome("aba"));
  assert(Solution::validPalindrome("abba"));
  assert(Solution::validPalindrome("abca"));
  assert(Solution::validPalindrome("abc") == false);

  return 0;
}
