// #include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
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
#define PB push_back

constexpr int MAX_N = 2*1e4;
std::array<std::array<ll, 2>, MAX_N> dp;

class Solution {
public:
  ll maximumValueSum(vi& nums, int k, const vvi& edges) {
    const auto n = CI(nums.size()); // 2 <= n <= 2 * 10^4
    vvi g(n);
    for (const auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    // std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), -1);

    const std::function<void(int,int)> dfs = [&](int v, int p) {
      if (p==-1 && g[v].size()==0) { // root & leaf
        dp[v][0] = nums[v];
        return;
      }
      if (p!=-1 && g[v].size()==1) { // leaf
        dp[v][0] = nums[v];
        dp[v][1] = nums[v]^k;
        return;
      }
      
      std::vector<std::pair<ll,int>> ch;
      ll dir_sum = 0, rev_sum = 0;
      for (const auto u : g[v]) {
        if (u == p) continue;
        dfs(u, v);
        ch.emplace_back(dp[u][1]-dp[u][0], u);
        dir_sum += dp[u][0];
      }
      dp[v][0] = dir_sum + nums[v];
      dp[v][1] = dir_sum + (nums[v]^k);
      std::sort(ch.rbegin(), ch.rend());

      FOR(i, 0, CI(ch.size())-1) {
        const auto rev_cnt = i+1;
        rev_sum += dp[ch[i].S][1];
        dir_sum -= dp[ch[i].S][0];
        if (rev_cnt%2 == 0) {
          dp[v][0] = std::max(dp[v][0], nums[v] + rev_sum + dir_sum);
          dp[v][1] = std::max(dp[v][1], (nums[v]^k) + rev_sum + dir_sum);
        } else {
          dp[v][0] = std::max(dp[v][0], (nums[v]^k) + rev_sum + dir_sum);
          dp[v][1] = std::max(dp[v][1], nums[v] + rev_sum + dir_sum);
        }
      }
    };
    
    dfs(0, -1);
    const auto res = dp[0][0];
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    vi nums{1,2,1};
    vvi edges{{0,1},{0,2}};
    const auto a_out = Solution().maximumValueSum(nums, 3, edges);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{2,3};
    vvi edges{{0,1}};
    const auto a_out = Solution().maximumValueSum(nums, 7, edges);
    assert(a_out == 9);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{7,7,7,7,7,7};
    vvi edges{{0,1},{0,2},{0,3},{0,4},{0,5}};
    const auto a_out = Solution().maximumValueSum(nums, 3, edges);
    assert(a_out == 42);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{24,78,1,97,44};
    vvi edges{{0,2},{1,2},{4,2},{3,4}};
    const auto a_out = Solution().maximumValueSum(nums, 6, edges);
    assert(a_out == 260);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{0,92,56,3,34,23,56};
    vvi edges{{2,6},{4,1},{5,0},{1,0},{3,1},{6,3}};
    const auto a_out = Solution().maximumValueSum(nums, 7, edges);
    assert(a_out == 288);

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