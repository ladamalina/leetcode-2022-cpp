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
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

constexpr std::array<ii, 2> DIRS{ii{1,0}, ii{0,1}};
constexpr int MOD = 1e9 + 7;
constexpr int MAX_N = 500;
std::array<std::array<std::array<int, MAX_N>, MAX_N>, 2> dp;
int m, n;

int Rec(const int d, const int i, const int j, const vvi& g) {
  if (i < 0 || i >= m || j < 0 || j >= n)
    return 0;
  if (i == m - 1 && j == n - 1)
    return 1;
  auto& res = dp[d][i][j];
  if (res != -1)
    return res;
  if (g[i][j]) {
    res = Rec(1 - d, i + DIRS[1-d].F, j + DIRS[1-d].S, g);
  } else {
    const auto res_0 = Rec(0, i + DIRS[0].F, j + DIRS[0].S, g);
    const auto res_1 = Rec(1, i + DIRS[1].F, j + DIRS[1].S, g);
    res = (CL(res_0) + CL(res_1)) % MOD;
  }
  return res;
}

class Solution {
public:
  int uniquePaths(const vvi& g) {
    m = SZ(g), n = SZ(g[0]);
    FOR(d, 0, 1) {
      auto& dp_d = dp[d];
      FOR(i, 0, m - 1) {
        std::fill(dp_d[i].begin(), dp_d[i].begin() + n, -1);
      }
    }
    return Rec(0, 0, 0, g);
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
