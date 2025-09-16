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

template <typename T>
class FenwickTree2 {
  /*
   * Range Update and Point Query
   * https://cp-algorithms.com/data_structures/fenwick.html#2-range-update-and-point-query
   */
public:
  explicit FenwickTree2(int n) : n_(n), bit_(n) {
  }

  explicit FenwickTree2(const std::vector<T>& a) : FenwickTree2(a.size()) {
    for (int i = 0; i < n_; ++i) {
      bit_[i] += a[i];
      int r = i | (i + 1);
      if (r < n_) bit_[r] += bit_[i];
    }
  }

  void Add(int idx, T delta) {
    for (++idx; idx < n_; idx += idx & -idx)
      bit_[idx] += delta;
  }

  void RangeAdd(int l, int r, int delta) {
    Add(l, delta);
    Add(r + 1, -delta);
  }

  T Get(int idx) {
    T ret = 0;
    for (++idx; idx > 0; idx -= idx & -idx)
      ret += bit_[idx];
    return ret;
  }

private:
  int n_;
  std::vector<T> bit_;
};

class Solution {
public:
  int maxFrequency(vi& nums, const int k, const int n_ops) {
    const auto n = SZ(nums);
    SORT(nums);
    const auto min_y = nums[0] - k, max_y = nums[n-1] + k;
    const auto max_v = max_y - min_y;
    FenwickTree2<int> tree_freq(max_v + 2), tree_cost(max_v + 2);
    FOR(i, 0, n-1) {
      const auto lo = nums[i] - k, hi = nums[i] + k;
      tree_freq.RangeAdd(lo - min_y, hi - min_y, 1);
      if (k) {
        tree_cost.RangeAdd(lo - min_y, nums[i] - 1 - min_y, 1);
        tree_cost.RangeAdd(nums[i] + 1 - min_y, hi - min_y, 1);
      }
    }
    int max_res = 1;
    FOR(y, min_y, max_y) {
      const auto v = y - min_y;
      const auto freq = tree_freq.Get(v);
      const auto cost = tree_cost.Get(v);
      if (cost <= n_ops) {
        max_res = std::max(max_res, freq);
      } else {
        const auto over = cost - n_ops;
        max_res = std::max(max_res, freq - over);
      }
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,4,5};
    const auto a_out = Solution().maxFrequency(nums, 1, 2);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{5,11,20,20};
    const auto a_out = Solution().maxFrequency(nums, 5, 1);
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
