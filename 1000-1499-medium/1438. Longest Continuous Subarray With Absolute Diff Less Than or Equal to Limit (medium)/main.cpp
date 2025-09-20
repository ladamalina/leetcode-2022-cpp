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
class SparseTableMin {
public:
  explicit SparseTableMin(const std::vector<T>& a) {
    const auto n = CI(a.size());
    const auto h_max = 31 - __builtin_clz(n);
    rmq_ = std::vector<std::vector<T>>(h_max+1, std::vector<T>(n));
    rmq_[0] = a;
    FOR(h, 1, h_max) {
      FOR(i, 0, n-(1<<h)) {
        rmq_[h][i] = std::min(rmq_[h-1][i], rmq_[h-1][i+(1<<(h-1))]);
      }
    }
  }

  T GetMin(int l, int r) const {
    const auto len = r - l + 1;
    const auto h = 31 - __builtin_clz(len);
    return std::min(rmq_[h][l], rmq_[h][r-(1<<h)+1]);
  }

private:
  std::vector<std::vector<T>> rmq_;
};

template<typename T>
class SparseTableMax {
public:
  explicit SparseTableMax(const std::vector<T>& a) {
    const auto n = CI(a.size());
    const auto h_max = 31 - __builtin_clz(n);
    rmq_ = std::vector<std::vector<T>>(h_max+1, std::vector<T>(n));
    rmq_[0] = a;
    FOR(h, 1, h_max) {
      FOR(i, 0, n-(1<<h)) {
        rmq_[h][i] = std::max(rmq_[h-1][i], rmq_[h-1][i+(1<<(h-1))]);
      }
    }
  }

  T GetMax(int l, int r) const {
    const auto len = r - l + 1;
    const auto h = 31 - __builtin_clz(len);
    return std::max(rmq_[h][l], rmq_[h][r-(1<<h)+1]);
  }

private:
  std::vector<std::vector<T>> rmq_;
};

class Solution {
public:
  int longestSubarray(const vi& nums, int limit) {
    const auto n = CI(nums.size());

    SparseTableMin rmq_mn(nums);
    SparseTableMax rmq_mx(nums);

    int res = 1;
    FOR(i, 0, n-1) {
      auto l=i, r=n-1;
      while (l<r) {
        const auto m = (l+r+1)/2;
        const auto mn = rmq_mn.GetMin(i, m);
        const auto mx = rmq_mx.GetMax(i, m);
        const auto diff = std::abs(CL(mx) - CL(mn));
        if (diff <= limit) l = m;
        else r = m-1;
      }
      res = std::max(res, r-i+1);
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{8,2,4,7};
    const auto a_out = Solution().longestSubarray(nums, 4);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{10,1,2,4,7,2};
    const auto a_out = Solution().longestSubarray(nums, 5);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{4,2,2,2,4,4,2,2};
    const auto a_out = Solution().longestSubarray(nums, 0);
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
