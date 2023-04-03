#include <cassert>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

using Partitioning = std::vector<std::vector<std::string>>;

class Solution {
 public:
  Partitioning partition(const std::string& s) {
    if (dp.count(s) != 0) {
      return dp.at(s);
    }
    if (s.size() == 1) {
      dp[s] = {{s}};
      return dp.at(s);
    } // len >= 2
    Partitioning s_ps;
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
      if (!IsPrefixPalindrome(s, i + 1)) {
        continue;
      }
      auto prefix = s.substr(0, i+1);
      if (prefix.size() == s.size()) {
        s_ps.push_back({prefix});
      } else {
        auto tail = s.substr(i+1);
        auto tail_ps = partition(tail);
        for (auto& tail_p : tail_ps) {
          std::vector<std::string> prefix_p{prefix};
          prefix_p.reserve(prefix_p.size() + tail_p.size());
          prefix_p.insert(prefix_p.end(),
                          std::make_move_iterator(tail_p.begin()),
                          std::make_move_iterator(tail_p.end()));
          s_ps.push_back(std::move(prefix_p));
        }
      }
    }
    dp[s] = std::move(s_ps);

    return dp.at(s);
  }

 private:
  std::unordered_map<std::string, Partitioning> dp;

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
  {
    Partitioning expected{{"a","a","b"},{"aa","b"}};
    assert(Solution().partition("aab") == expected);
  }
  {
    Partitioning expected{{"e","f","e"},{"efe"}};
    assert(Solution().partition("efe") == expected);
  }
  {
    Partitioning expected{{"a"}};
    assert(Solution().partition("a") == expected);
  }
}
