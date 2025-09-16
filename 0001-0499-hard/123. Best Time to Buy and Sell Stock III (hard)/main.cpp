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
  static int maxProfit(const vi& prices) {
    const auto n = CI(prices.size());
    if (n == 1)
      return 0;
    
    vi pref_min(n);
    pref_min[0] = prices[0];
    FOR(i, 1, n-1) {
      pref_min[i] = std::min(pref_min[i-1], prices[i]);
    }

    vi suff_max(n);
    suff_max[n-1] = prices[n-1];
    FORD(i, n-2, 0) {
      suff_max[i] = std::max(suff_max[i+1], prices[i]);
    }

    vi max_profit_pref(n);
    max_profit_pref[0] = 0;
    FOR(i, 1, n-1) {
      max_profit_pref[i] = std::max(max_profit_pref[i-1], prices[i]-pref_min[i-1]);
    }

    vi max_profit_suff(n);
    max_profit_suff[n-1] = 0;
    FORD(i, n-2, 0) {
      max_profit_suff[i] = std::max(max_profit_suff[i+1], suff_max[i+1]-prices[i]);
    }

    int max_profit = 0;
    FOR(i, 0, n-1) {
      const auto max_profit_before = max_profit_pref[i];
      const auto max_profit_after = (i+1 < n) ? max_profit_suff[i+1] : 0;
      const auto profit = std::max(0, max_profit_before) + std::max(0, max_profit_after);
      max_profit = std::max(max_profit, profit);
    }
    return max_profit;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vi prices{3,3,5,0,0,3,1,4};
    const auto a_out = Solution::maxProfit(prices);
    assert(a_out == 6);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vi prices{1,2,3,4,5};
    const auto a_out = Solution::maxProfit(prices);
    assert(a_out == 4);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vi prices{7,6,4,3,1};
    const auto a_out = Solution::maxProfit(prices);
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
