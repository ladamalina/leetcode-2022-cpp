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
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
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
#define F first
#define S second

template<typename T>
class FenwickTree2 {
  /*
   * Range Update and Point Query
   * https://cp-algorithms.com/data_structures/fenwick.html#2-range-update-and-point-query
   */
public:
  explicit FenwickTree2(int n) : n_(n), bit_(n) {}

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
    Add(r+1, -delta);
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
  int minKBitFlips(const vi& nums, int k) {
    const auto n = CI(nums.size());
    FenwickTree2<int> tree(n+1);

    int res = 0;
    bool ok = true;
    FOR(i, 0, n-1) {
      const auto revs = tree.Get(i);
      const auto x = (revs%2 == 0) ? nums[i] : 1-nums[i];
      if (x == 0) {
        if (n-i < k) { ok = false; break; }
        tree.RangeAdd(i, i+k-1, 1);
        ++res;
      }
    }
    return ok ? res : -1;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{0,1,0};
    const auto a_out = Solution().minKBitFlips(nums, 1);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,0};
    const auto a_out = Solution().minKBitFlips(nums, 2);
    assert(a_out == -1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{0,0,0,1,0,1,1,0};
    const auto a_out = Solution().minKBitFlips(nums, 3);
    assert(a_out == 3);
  
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
