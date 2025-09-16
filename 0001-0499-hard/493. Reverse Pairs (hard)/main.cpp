#include <bits/stdc++.h>

/*#include <algorithm>
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
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>*/

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
class FenwickTree {
  /*
   * Point Update and Range Query
   * https://cp-algorithms.com/data_structures/fenwick.html
   */
public:
  explicit FenwickTree(int n) : n_(n), bit_(n) {}

  explicit FenwickTree(const std::vector<T>& a) : FenwickTree(a.size()) {
    for (int i = 0; i < n_; ++i) {
      bit_[i] += a[i];
      int r = i | (i + 1);
      if (r < n_) bit_[r] += bit_[i];
    }
  }

  void Add(int idx, T delta) {
    for (; idx < n_; idx |= (idx + 1))
      bit_[idx] += delta;
  }

  T Sum(int l, int r) const {
    return Sum(r) - Sum(l - 1);
  }

  T Sum(int r) const {
    T res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      res += bit_[r];
    return res;
  }
  
private:
  int n_;
  std::vector<T> bit_;
};

class Solution {
public:
  int reversePairs(const vi& nums) {
    const auto n = CI(nums.size());
    
    vl x_vec(RNG(nums));
    std::sort(RNG(x_vec));
    x_vec.erase(std::unique(RNG(x_vec)), x_vec.end());
    const auto un = CI(x_vec.size());

    std::map<ll, int> x_comp;
    for (const auto x : x_vec) {
      if (!x_comp.contains(x))
        x_comp[x] = x_comp.size();
    }

    FenwickTree<int> tree(un);
    ll res = 0;
    FOR(i, 0, n-1) {
      const auto lb = CL(nums[i])*2+1;
      const auto it = x_comp.lower_bound(lb);
      if (it != x_comp.end()) {
        const auto lb_comp = it->S;
        const auto loc_res = tree.Sum(lb_comp, un-1);
        res += loc_res;
      }
      tree.Add(x_comp[nums[i]], 1);
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,3,2,3,1};
    const auto a_out = Solution().reversePairs(nums);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,4,3,5,1};
    const auto a_out = Solution().reversePairs(nums);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2147483647,2147483647,2147483647,2147483647,2147483647,2147483647};
    const auto a_out = Solution().reversePairs(nums);
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
