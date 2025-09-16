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
  static int maxProfit(const int k, const vi& prices) {
    const auto n = CI(prices.size());

    // dp[i].F: Best profit with under i transactions completed and one new transaction started
    // dp[i].S: Best profit in i or less transactions
    vii dp(k, {INT_MIN, 0});
    
    FOR(i, 0, n-1) {
      dp[0].F = std::max(dp[0].F, -prices[i]);
      dp[0].S = std::max(dp[0].S, dp[0].F + prices[i]);
      FOR(j, 1, k-1) {
        dp[j].F = std::max(dp[j].F, dp[j-1].S - prices[i]);
        dp[j].S = std::max(dp[j].S, dp[j].F + prices[i]);
      }
    }

    return dp[k-1].S;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vi prices{2,4,1};
    const auto a_out = Solution::maxProfit(2, prices);
    assert(a_out == 2);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vi prices{3,2,6,5,0,3};
    const auto a_out = Solution::maxProfit(2, prices);
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
