// #pragma GCC optimize("O3,unroll-loops")
// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
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
#include <numbers>
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

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> sl, sr;
std::array<ll, MAX_N> psum;

bool Intersect(const int a, const int b, const int c, const int d) {
  return std::max(a, c) <= std::min(b, d);
}

class Solution {
public:
  vl countStableSubarrays(const vi& nums, const vvi& queries) {
    const auto n = SZ(nums), qn = SZ(queries);
    sl[0] = 0;
    FOR(i, 1, n-1) sl[i] = nums[i-1] <= nums[i] ? sl[i-1] : i;
    sr[n-1] = n-1;
    FORD(i, n-2, 0) sr[i] = nums[i] <= nums[i+1] ? sr[i+1] : i;
    FOR(i, 0, n-1) {
      if (i == sl[i]) {
        const auto len = sr[i] - sl[i] + 1;
        psum[i] = CL(1 + len) * len / 2 + (i > 0 ? psum[i-1] : 0);
      } else {
        psum[i] = i > 0 ? psum[i-1] : 0;
      }
    }
    vl res(qn);
    FOR(qi, 0, qn - 1) {
      const auto l = queries[qi][0], r = queries[qi][1];
      const auto lr = std::min(sr[l], r), pref_len = lr - l + 1;
      const auto pref = CL(1 + pref_len) * pref_len / 2;
      const auto rl = std::max(sl[r], l), suff_len = r - rl + 1;
      if (Intersect(l, lr, rl, r)) {
        res[qi] = pref;
        continue;
      }
      const auto suff = CL(1 + suff_len) * suff_len / 2;
      if (lr + 1 > rl) {
        res[qi] = pref + suff;
        continue;
      }
      const auto mid_sum = psum[rl - 1] - psum[lr];
      res[qi] = pref + mid_sum + suff;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{3,1,2};
    const vvi queries{{0,1},{1,2},{0,2}};
    const auto a_out = Solution().countStableSubarrays(nums, queries);
    const vl e_out{2,3,4};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,2};
    const vvi queries{{0,1},{0,0}};
    const auto a_out = Solution().countStableSubarrays(nums, queries);
    const vl e_out{3,1};
    assert(a_out == e_out);
  
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
