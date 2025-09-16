#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int minCut(const std::string& s) {
    if (s.size() == 1) {
      return 0;
    } // len >= 2
    if (dp.count(s) != 0) {
      return dp.at(s);
    }
    int min_cuts = static_cast<int>(s.size());
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
      if (!IsPrefixPalindrome(s, i+1)) {
        continue;
      }
      if (i+1 == static_cast<int>(s.size())) {
        min_cuts = 0;
      } else {
        auto tail = s.substr(i+1);
        auto tail_min_cuts = minCut(tail);
        min_cuts = std::min(min_cuts, tail_min_cuts + 1);
      }
    }
    dp[s] = min_cuts;

    return dp.at(s);
  }

 private:
  std::unordered_map<std::string, int> dp;

  static bool IsPrefixPalindrome(const std::string& s, int prefix_len) {
    int l_idx = 0;
    int r_idx = prefix_len - 1;
    while (l_idx <= r_idx) {
      if (s[l_idx] != s[r_idx]) {
        return false;
      }
      ++l_idx;
      --r_idx;
    }
    return true;
  }
};

int main() {
  assert(Solution().minCut("aab") == 1);
  assert(Solution().minCut("a") == 0);
  assert(Solution().minCut("ab") == 1);
  assert(Solution().minCut("bb") == 0);
}
