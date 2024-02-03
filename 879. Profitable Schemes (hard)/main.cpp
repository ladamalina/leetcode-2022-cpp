#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

constexpr int MAX_N = 100;
constexpr int MAX_PROFIT = 10000;
int dp[MAX_N+1][MAX_PROFIT+1];

constexpr int MOD = 1e9 + 7;

class Solution {
 public:
  static int profitableSchemes(int n, int min_profit, const vi& group, const vi& profit) {
    memset(&dp, 0, sizeof(dp));
    dp[0][0] = 1;
    const auto m = CI(group.size());
    const auto max_profit = std::accumulate(RNG(profit), 0);
    for (int i = 0; i < m; ++i) {
      const auto g = group[i];
      const auto p = profit[i];
      for (auto j = n; j >= g; --j) {
        for (auto k = max_profit; k >= p; --k) {
          dp[j][k] = (dp[j][k] + dp[j-g][k-p]) % MOD;
        }
      }
    }
    ll res = 0;
    FOR(i, 0, n) {
      FOR(j, min_profit, max_profit) {
        res = (res + dp[i][j]) % MOD;
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::profitableSchemes(5, 3, {2,2}, {2,3});
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::profitableSchemes(10, 5, {2,3,5}, {6,7,8});
    assert(a_out == 7);

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
