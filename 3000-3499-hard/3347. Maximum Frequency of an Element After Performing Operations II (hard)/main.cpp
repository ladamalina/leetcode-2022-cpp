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
  int maxFrequency(const vi& nums, const int k, const int n_ops) {
    const auto n = SZ(nums);
    std::unordered_map<int, int> x_comp;
    {
      vi xs;
      xs.reserve(n * 5);
      for (const auto x : nums) {
        xs.push_back(x);
        xs.push_back(x - 1);
        xs.push_back(x - k);
        xs.push_back(x + 1);
        xs.push_back(x + k);
      }
      SORT(xs);
      xs.erase(std::unique(RNG(xs)), xs.end());
      for (const auto x : xs) x_comp[x] = SZ(x_comp);
    }
    const auto nx = SZ(x_comp);

    FenwickTree2<int> tree_freq(nx + 2), tree_cost(nx + 2);
    for (const auto x : nums) {
      tree_freq.RangeAdd(x_comp[x], x_comp[x], 1);
      if (k) {
        tree_freq.RangeAdd(x_comp[x-k], x_comp[x-1], 1);
        tree_freq.RangeAdd(x_comp[x+1], x_comp[x+k], 1);
        tree_cost.RangeAdd(x_comp[x-k], x_comp[x-1], 1);
        tree_cost.RangeAdd(x_comp[x+1], x_comp[x+k], 1);
      }
    }

    int max_res = 0;
    FOR(y, 0, nx - 1) {
      const auto freq = tree_freq.Get(y), cost = tree_cost.Get(y);
      if (cost <= n_ops) {
        max_res = std::max(max_res, freq);
      } else {
        const auto over = cost - n_ops;
        const auto res = std::max(freq - over, 0);
        max_res = std::max(max_res, res);
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
