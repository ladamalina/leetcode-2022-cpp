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

constexpr int MOD = 1e9 + 7, MAX_N = 300, MAX_X = 5;
std::array<std::array<int, MAX_N + 1>, MAX_X + 1> x_n_pow;
std::array<bool, MAX_X + 1> init_x_n_pow{};
void InitXArr(const int x) {
  if (init_x_n_pow[x]) return;
  std::fill(RNG(x_n_pow[x]), INT_MAX);
  FOR(n, 1, MAX_N) {
    auto val = n, pow = 1;
    while (pow < x && val * n <= MAX_N) {
      ++pow;
      val *= n;
    }
    if (pow == x) x_n_pow[x][n] = val;
  }
  init_x_n_pow[x] = true;
}
std::array<int, MAX_N + 1> dp;

class Solution {
public:
  int numberOfWays(const int n, const int x) {
    InitXArr(x);
    std::fill(dp.begin(), dp.begin() + n + 1, 0);
    dp[0] = 1;
    const auto& n_pow = x_n_pow[x];
    FORD(i, n, 1) {
      FORD(j, n, n_pow[i]) {
        dp[j] = (CL(dp[j]) + dp[j - n_pow[i]]) % MOD;
      }
    }
    return dp[n];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().numberOfWays(10, 2);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().numberOfWays(4, 1);
    assert(a_out == 2);
  
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
