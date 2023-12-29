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
using vvvi [[maybe_unused]] = std::vector<vvi>;
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
  static int countDigitOne(const int n) {
    vvvi dp(10, vvi(10, vi(2, -1)));
    std::function<int(int, std::string, int, bool)> rec = [&](int idx, const std::string& s, int cnt, bool sm) {
      if (idx == CI(s.size())) return cnt;
      if (dp[idx][cnt][sm] != -1) return dp[idx][cnt][sm];
      const int limit = sm ? 9 : s[idx] - '0';
      int ans = 0;
      FOR(i, 0, limit) {
        const auto upd_cnt = cnt + (i == 1);
        const auto upd_sm = (!sm && i == limit) ? false : true;
        ans += rec(idx + 1, s, upd_cnt, upd_sm);
      }
      dp[idx][cnt][sm] = ans;
      return ans;
    };
    const auto n_str = std::to_string(n);
    const auto res = rec(0, n_str, 0, false);

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const int n = 13;
    const auto a_out = Solution::countDigitOne(n);
    assert(a_out == 6);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const int n = 0;
    const auto a_out = Solution::countDigitOne(n);
    assert(a_out == 0);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
