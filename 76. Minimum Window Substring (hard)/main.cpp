//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

class Solution {
 public:
  static std::string minWindow(const std::string& s, const std::string& t) {
    const std::unordered_set<char> t_chars(RNG(t));
    std::unordered_map<char, int> diff;
    for (const auto ch : t)
      --diff[ch];

    const auto s_len = CI(s.size());

    int l = -1;
    int r = -1;

    int min_len = INT_MAX;
    int best_l = l;
    int best_r = r;

    auto mv_l = [&]() {
      if (l >= 0 && t_chars.contains(s[l])) {
        --diff[s[l]];
        if (diff[s[l]] == 0)
          diff.erase(s[l]);
      }
      ++l;
    };

    auto mv_r = [&]() {
      ++r;
      if (t_chars.contains(s[r])) {
        ++diff[s[r]];
        if (diff[s[r]] == 0)
          diff.erase(s[r]);
      }
    };
    
    auto eq = [&]() {
      return std::find_if(RNG(diff), [](const auto& d) { return d.S < 0; }) == diff.end();
    };

    while (r+1 < s_len) {
      while (r+1 < s_len && !eq()) {
        mv_r();
      }
      if (!eq())
        break;
      while (l <= r && eq()) {
        if (r-l+1 < min_len) {
          min_len = r-l+1;
          best_l = l;
          best_r = r;
        }
        mv_l();
      }
    }

    return min_len == INT_MAX ? "" : s.substr(best_l, best_r-best_l+1);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s("ADOBECODEBANC");
    const std::string t("ABC");
    const auto a_out = Solution::minWindow(s, t);
    assert(a_out == "BANC");
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s("a");
    const std::string t("a");
    const auto a_out = Solution::minWindow(s, t);
    assert(a_out == "a");
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s("a");
    const std::string t("aa");
    const auto a_out = Solution::minWindow(s, t);
    assert(a_out == "");
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s("cabwefgewcwaefgcf");
    const std::string t("cae");
    const auto a_out = Solution::minWindow(s, t);
    assert(a_out == "cwae");
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ");
    const std::string t("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ");
    const auto a_out = Solution::minWindow(s, t);
    assert(a_out == "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ");
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
