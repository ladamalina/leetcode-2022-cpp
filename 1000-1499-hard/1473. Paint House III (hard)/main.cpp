// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
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
using vvl [[maybe_unused]] = std::vector<vl>;
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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

class Solution {
public:
  int minCost(const vi& houses, const vvi& cost, int n_houses, int n_colors, int target) {
    std::vector<vvi> dp(n_houses, vvi(target+1, vi(n_colors+1, INT_MAX)));
    if (houses[0] == 0) {
      FOR(c, 1, n_colors) {
        dp[0][1][c] = cost[0][c-1];
      }
    } else {
      dp[0][1][houses[0]] = 0;
    }
    FOR(i, 1, n_houses-1) {
      FOR(prev_j, 1, target) {
        FOR(prev_c, 1, n_colors) {
          if (dp[i-1][prev_j][prev_c] == INT_MAX)
            continue;
          if (houses[i] == 0) {
            FOR(c, 1, n_colors) {
              if (prev_c == c) {
                dp[i][prev_j][c] = std::min(dp[i][prev_j][c], dp[i-1][prev_j][prev_c] + cost[i][c-1]);
              } else if (prev_j + 1 <= target) {
                dp[i][prev_j+1][c] = std::min(dp[i][prev_j+1][c], dp[i-1][prev_j][prev_c] + cost[i][c-1]);
              }
            }
          } else {
            if (prev_c == houses[i]) {
              dp[i][prev_j][houses[i]] = std::min(dp[i][prev_j][houses[i]], dp[i-1][prev_j][prev_c]);
            } else if (prev_j + 1 <= target) {
              dp[i][prev_j+1][houses[i]] = std::min(dp[i][prev_j+1][houses[i]], dp[i-1][prev_j][prev_c]);
            }
          }
        }
      }
    }
    auto min_res = INT_MAX;
    FOR(c, 1, n_colors) {
      min_res = std::min(min_res, dp[n_houses-1][target][c]);
    }
    return (min_res == INT_MAX) ? -1 : min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi houses{0,0,0,0,0};
    const vvi costs{{1,10},{10,1},{10,1},{1,10},{5,1}};
    const auto a_out = Solution().minCost(houses, costs, 5, 2, 3);
    assert(a_out == 9);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi houses{0,2,1,2,0};
    const vvi costs{{1,10},{10,1},{10,1},{1,10},{5,1}};
    const auto a_out = Solution().minCost(houses, costs, 5, 2, 3);
    assert(a_out == 11);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi houses{3,1,2,3};
    const vvi costs{{1,1,1},{1,1,1},{1,1,1},{1,1,1}};
    const auto a_out = Solution().minCost(houses, costs, 4, 3, 3);
    assert(a_out == -1);
  
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
