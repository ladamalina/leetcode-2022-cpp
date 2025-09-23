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

constexpr std::array<ii, 3> DIRS2{ii{1,-1},ii{1,0},ii{1,1}};
constexpr std::array<ii, 3> DIRS3{ii{-1,1},ii{0,1},ii{1,1}};
constexpr int MAX_N = 1000;
std::array<std::array<int, MAX_N>, MAX_N> dp;

class Solution {
public:
  int maxCollectedFruits(const vvi& g) {
    n = SZ(g);
    const auto res1 = Case1(g);
    const auto res2 = Case2(g);
    const auto res3 = Case3(g);
    return res1 + res2 + res3;
  }
private:
  int n = 0;
  [[nodiscard]] int Case1(const vvi& g) const {
    auto res = 0;
    FOR(i, 0, n-1) res += g[i][i];
    return res;
  }
  int Rec2(const int i, const int j, const vvi& g) {
    if (i >= j) return 0;
    auto& res = dp[i][j];
    if (res != -1) return res;
    res = 0;
    for (const auto [di, dj] : DIRS2) {
      const auto ni = i + di, nj = j + dj;
      if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
        res = std::max(res, g[i][j] + Rec2(ni, nj, g));
      }
    }
    return res;
  }
  int Case2(const vvi& g) {
    FOR(i, 0, n-1) std::fill(dp[i].begin(), dp[i].begin() + n, -1);
    return Rec2(0, n-1, g);
  }
  int Rec3(const int i, const int j, const vvi& g) {
    if (i <= j) return 0;
    auto& res = dp[i][j];
    if (res != -1) return res;
    res = 0;
    for (const auto [di, dj] : DIRS3) {
      const auto ni = i + di, nj = j + dj;
      if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
        res = std::max(res, g[i][j] + Rec3(ni, nj, g));
      }
    }
    return res;
  }
  int Case3(const vvi& g) {
    FOR(i, 0, n-1) std::fill(dp[i].begin(), dp[i].begin() + n, -1);
    return Rec3(n-1, 0, g);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi fruits{{1,1},{1,1}};
    const auto a_out = Solution().maxCollectedFruits(fruits);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi fruits{{1,2,3,4},{5,6,8,7},{9,10,11,12},{13,14,15,16}};
    const auto a_out = Solution().maxCollectedFruits(fruits);
    assert(a_out == 100);
  
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
