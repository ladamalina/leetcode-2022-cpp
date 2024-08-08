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
  vi countOfPeaks(vi& nums, const vvi& queries) {
    const auto n = CI(nums.size());
    vi peak(n);
    FOR(i, 1, n-2) {
      peak[i] = (nums[i-1]<nums[i] && nums[i]>nums[i+1]);
    }
    FenwickTree tree(peak);

    const auto is_peak = [&](int i) {
      return (i-1>=0 && i+1<n && nums[i-1]<nums[i] && nums[i]>nums[i+1]);
    };
    
    vi res;
    for (const auto& q : queries) {
      if (q[0] == 1) {
        const auto l = q[1];
        const auto r = q[2];
        if (r-l+1 <= 2) res.push_back(0);
        else {
          const auto q_res = tree.Sum(l+1, r-1);
          res.push_back(q_res);
        }
      } else {
        const auto i = q[1];
        nums[i] = q[2];
        {
          const auto upd = is_peak(i);
          tree.Add(i, upd-peak[i]);
          peak[i] = upd;
        }
        if (i-1>=0) {
          const auto upd = is_peak(i-1);
          tree.Add(i-1, upd-peak[i-1]);
          peak[i-1] = upd;
        }
        if (i+1<n) {
          const auto upd = is_peak(i+1);
          tree.Add(i+1, upd-peak[i+1]);
          peak[i+1] = upd;
        }
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{3,1,4,2,5};
    const vvi queries{{2,3,4},{1,0,4}};
    const auto a_out = Solution().countOfPeaks(nums, queries);
    const vi e_out{0};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{4,1,4,2,1,5};
    const vvi queries{{2,2,4},{1,0,2},{1,0,4}};
    const auto a_out = Solution().countOfPeaks(nums, queries);
    const vi e_out{0,1};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{10,6,7,5,5,4,7,10,7};
    const vvi queries{{1,2,5},{2,5,7},{1,0,8},{1,5,7},{1,1,5}};
    const auto a_out = Solution().countOfPeaks(nums, queries);
    const vi e_out{0,2,0,1};
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
