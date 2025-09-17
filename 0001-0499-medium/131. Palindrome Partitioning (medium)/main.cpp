// #include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second
#define PB push_back

class Solution {
 public:
  vvs partition(const std::string& s) {
    return rec(s, 0, CI(s.size()));
  }

 private:
  std::unordered_map<std::string_view, vvs> dp;

  vvs rec(const std::string& s, int l, int n) {
    if (l == n) return {};
    const auto tail_s = s.substr(l, n-l);
    if (dp.contains(tail_s)) return dp.at(tail_s);
    
    vvs res;
    FOR(r, l, n-1) {
      if (IsPalindrome(s, l, r)) {
        const auto pref = s.substr(l, r-l+1);
        if (r == n-1) {
          res.push_back({pref});
        } else {
          auto sub_res = rec(s, r+1, n);
          for (auto& sub_p : sub_res) {
            vs res_p{pref};
            res_p.insert(res_p.end(), std::make_move_iterator(sub_p.begin()),std::make_move_iterator(sub_p.end()));
            res.push_back(std::move(res_p));
          }
        }
      }
    }
    dp[s] = std::move(res);
    return dp.at(s);
  }

  static bool IsPalindrome(const std::string& s, int l, int r) {
    while (l < r) {
      if (s[l] != s[r]) return false;
      ++l; --r;
    }
    return true;
  }
};

int main() {
  {
    const vvs exp{{"a","a","b"},{"aa","b"}};
    const auto act = Solution().partition("aab"s);
    assert(act == exp);
  }
  {
    const vvs exp{{"e","f","e"},{"efe"}};
    const auto act = Solution().partition("efe"s);
    assert(act == exp);
  }
  {
    const vvs exp{{"a"}};
    const auto act = Solution().partition("a"s);
    assert(act == exp);
  }
}
