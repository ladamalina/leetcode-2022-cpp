#include <bits/stdc++.h>

/*#include <algorithm>
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
#include <vector>*/

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

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second

void Rec(int v, int p, const vvi& g, const vi& coins, int k, vvi& dp, vvi& par_sum) {
  for (const auto u : g[v]) {
    if (u == p) continue;
    Rec(u, v, g, coins, k, dp, par_sum);
  }
  
  auto v_coins = coins[v];
  FOR(i, 0, 14) {
    // no div
    dp[v][i] = std::max(dp[v][i], v_coins-k + par_sum[v][i]);

    // div
    v_coins /= 2;
    if (i+1 < 15) dp[v][i] = std::max(dp[v][i], v_coins + par_sum[v][i+1]);

    if (p != -1) par_sum[p][i] += dp[v][i];
  }
}

class Solution {
public:
  int maximumPoints(const vvi& edges, const vi& coins, int k) {
    const auto n = CI(edges.size())+1;
    vvi g(n);
    for (const auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }

    vvi dp(n, vi(15, INT_MIN));
    vvi par_sum(n, vi(15));
    Rec(0, -1, g, coins, k, dp, par_sum);
    return dp[0][0];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{1,2},{2,3}};
    const vi coins{10,10,3,3};
    const auto a_out = Solution().maximumPoints(edges, coins, 5);
    assert(a_out == 11);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{0,2}};
    const vi coins{8,4,4};
    const auto a_out = Solution().maximumPoints(edges, coins, 0);
    assert(a_out == 16);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,0},{2,1},{3,1}};
    const vi coins{8,2,7,1};
    const auto a_out = Solution().maximumPoints(edges, coins, 2);
    assert(a_out == 11);
  
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
