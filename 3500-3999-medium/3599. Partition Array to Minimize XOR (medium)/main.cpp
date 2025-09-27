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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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

constexpr int MAX_N = 250;
std::array<int, MAX_N> pxor;
std::array<std::array<int, MAX_N+1>, MAX_N> dp;
int n;

int Rec(const int i, const int c) {
  if (i == n)
    return c == 0 ? 0 : INT_MAX;
  // i < n
  if (c == 0) return INT_MAX;
  if (c == 1) return pxor[n-1] ^ (i > 0 ? pxor[i-1] : 0);
  // c > 1

  auto& res = dp[i][c];
  if (res != -1) return res;
  res = INT_MAX;
  FOR(j, i, n-c) {
    const auto i_xor = pxor[j] ^ (i > 0 ? pxor[i-1] : 0);
    const auto sub_res = Rec(j+1, c-1);
    res = std::min(res, std::max(i_xor, sub_res));
  }
  return res;
}

class Solution {
public:
  int minXor(const vi& nums, int k) {
    n = SZ(nums);
    FOR(i, 0, n-1) pxor[i] = nums[i] ^ (i > 0 ? pxor[i-1] : 0);

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), -1);

    vvi dp(n, vi(k+1, -1));
    const auto res = Rec(0, k);

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,3};
    const auto a_out = Solution().minXor(nums, 2);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,3,3,2};
    const auto a_out = Solution().minXor(nums, 3);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,2,3,1};
    const auto a_out = Solution().minXor(nums, 2);
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
