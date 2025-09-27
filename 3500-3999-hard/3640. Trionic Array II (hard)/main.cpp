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

constexpr int MAX_N = 1e5;
std::array<ll, MAX_N> inc_dir, inc_rev, dec_sum;
std::array<int, MAX_N> dec_idx;

class Solution {
public:
  ll maxSumTrionic(const vi& nums) {
    const auto n = SZ(nums);

    FORD(i, n-1, 0) {
      if (i != n-1 && nums[i] < nums[i+1]) {
        inc_dir[i] = nums[i+1];
        if (inc_dir[i+1] != LLONG_MIN) inc_dir[i] = std::max(inc_dir[i], nums[i+1] + inc_dir[i+1]);
      } else {
        inc_dir[i] = LLONG_MIN;
      }
    }
    FOR(i, 0, n-1) {
      if (i != 0 && nums[i-1] < nums[i]) {
        inc_rev[i] = nums[i-1];
        if (inc_rev[i-1] != LLONG_MIN) inc_rev[i] = std::max(inc_rev[i], nums[i-1] + inc_rev[i-1]);
      } else {
        inc_rev[i] = LLONG_MIN;
      }
    }
    FORD(i, n-1, 0) {
      dec_idx[i] = i;
      dec_sum[i] = nums[i];
      if (i != n-1 && nums[i] > nums[i+1]) {
        dec_idx[i] = dec_idx[i+1];
        dec_sum[i] += dec_sum[i+1];
      }
    }

    ll max_res = LLONG_MIN;
    FOR(i, 0, n-1) {
      if (dec_idx[i] != i && inc_rev[i] != LLONG_MIN && inc_dir[dec_idx[i]] != LLONG_MIN) {
        max_res = std::max(max_res, dec_sum[i] + inc_rev[i] + inc_dir[dec_idx[i]]);
      }
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{0,-2,-1,-3,0,2,-1};
    const auto a_out = Solution().maxSumTrionic(nums);
    assert(a_out == -4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,4,2,7};
    const auto a_out = Solution().maxSumTrionic(nums);
    assert(a_out == 14);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{-602,442,-814,803,-26};
    const auto a_out = Solution().maxSumTrionic(nums);
    assert(a_out == -171);
  
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
