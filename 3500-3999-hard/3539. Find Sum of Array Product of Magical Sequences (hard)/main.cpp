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
#include <queue>
#include <random>
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

constexpr int MOD = 1e9 + 7;
[[maybe_unused]] constexpr int MAX_K = 30, MAX_M = 30, MAX_N = 50;
static int dp[31][31][50][31];

// Binomial Coefficients / O(N^2), iterative
// https://cp-algorithms.com/combinatorics/binomial-coefficients.html
constexpr int MAX_CN = 30;
std::array<std::array<int, MAX_CN + 1>, MAX_CN + 1> bin_c;
bool init_comb = false;
void InitComb() {
  if (init_comb) return;
  bin_c[0][0] = 1;
  FOR(i, 1, MAX_CN) {
    bin_c[i][0] = bin_c[i][i] = 1;
    FOR(k, 1, MAX_CN - 1) { bin_c[i][k] = bin_c[i - 1][k - 1] + bin_c[i - 1][k]; }
  }
  init_comb = true;
}

int DFS(const int m, const int k, const int i, unsigned flag, const vi& nums) {
  const int n_bits = __builtin_popcount(flag);
  if (m < 0 || k < 0 || m + n_bits < k) return 0;
  if (m == 0) return (k == n_bits) ? 1 : 0;
  if (i >= SZ(nums)) return 0;

  auto& ans = dp[m][k][i][flag];
  if (ans != -1) return ans;
  ans = 0;

  ll pow_x = 1;
  const int x = nums[i];
  for (int f = 0; f <= m; f++) {
    ll perm = (CL(bin_c[m][f]) * pow_x) % MOD;

    unsigned new_flag = flag + f;
    unsigned next_flag = new_flag >> 1;
    bool bit_set = new_flag & 1;

    ans = (ans + perm * DFS(m - f, k - bit_set, i + 1, next_flag, nums)) % MOD;
    pow_x = (pow_x * x) % MOD;
  }

  return ans;
}

class Solution {
 public:
  int magicalSum(const int m, const int k, const vi& nums) {
    InitComb();
    for (int i = 0; i <= m; ++i)
      for (int j = 0; j <= m; ++j)
        for (int s = 0; s < SZ(nums); ++s) memset(dp[i][j][s], -1, sizeof(int) * (m + 1));

    return DFS(m, k, 0, 0, nums);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1, 10, 100, 10000, 1000000};
    const auto a_out = Solution().magicalSum(5, 5, nums);
    assert(a_out == 991600007);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{5, 4, 3, 2, 1};
    const auto a_out = Solution().magicalSum(2, 2, nums);
    assert(a_out == 170);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{28};
    const auto a_out = Solution().magicalSum(1, 1, nums);
    assert(a_out == 28);

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
