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

constexpr ll MOD = 1e9 + 7;
constexpr int MAX_N = 50, MAX_K = 10;
std::array<std::array<int, MAX_N>, MAX_N> a;
std::array<std::array<std::array<ll, MAX_K+1>, MAX_N>, MAX_N> dp;
int n, m;

int CountA(const int i0, const int j0, const int i1, const int j1) {
  return a[i1][j1] - (i0>0 ? a[i0-1][j1] : 0) - (j0>0 ? a[i1][j0-1] : 0) + (i0>0 && j0>0 ? a[i0-1][j0-1] : 0);
}

ll Rec(const int i, const int j, const int k) {
  if (i >= n || j >= m)
    return 0;
  // i < n && j < m
  
  if (k == 1) {
    return CountA(i, j, n-1, m-1) > 0;
  }
  // i < n && j < m && k > 1
  
  if (dp[i][j][k] != -1)
    return dp[i][j][k];

  dp[i][j][k] = 0;
  FOR(i1, i, n-2) {
    if (CountA(i, j, i1, m-1) > 0) {
      dp[i][j][k] = (dp[i][j][k] + Rec(i1+1, j, k-1)) % MOD;
    }
  }
  FOR(j1, j, m-2) {
    if (CountA(i, j, n-1, j1) > 0) {
      dp[i][j][k] = (dp[i][j][k] + Rec(i, j1+1, k-1)) % MOD;
    }
  }
  return dp[i][j][k];
}

class Solution {
public:
  int ways(const vs& pizza, const int k) {
    n = SZ(pizza), m = SZ(pizza[0]);

    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        a[i][j] = (pizza[i][j] == 'A') + (i>0 ? a[i-1][j] : 0) + (j>0 ? a[i][j-1] : 0) - (i>0 && j>0 ? a[i-1][j-1] : 0);
      }
    }
    
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(dp[0][0][0]), -1);
    const auto res = Rec(0, 0, k);

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs pizza{"A..","AAA","..."};
    const auto a_out = Solution().ways(pizza, 3);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs pizza{"A..","AA.","..."};
    const auto a_out = Solution().ways(pizza, 3);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs pizza{"A..","A..","..."};
    const auto a_out = Solution().ways(pizza, 1);
    assert(a_out == 1);
  
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
