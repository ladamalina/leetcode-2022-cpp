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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

template <typename T>
class SparseTable {
public:
  explicit SparseTable(const std::vector<T>& a) {
    const auto n = CI(a.size());
    const auto h_max = 31 - __builtin_clz(n);
    //    const auto h_max = std::ceil(std::log2(n));
    rmq_ = std::vector<std::vector<T>>(h_max + 1, std::vector<T>(n));
    rmq_[0] = a;
    FOR(h, 1, h_max) {
      FOR(i, 0, n-(1<<h)) {
        rmq_[h][i] = std::min(rmq_[h - 1][i], rmq_[h - 1][i + (1 << (h - 1))]);
      }
    }
  }

  T GetMin(int l, int r) const {
    const auto len = r - l + 1;
    const auto h = 31 - __builtin_clz(len);
    return std::min(rmq_[h][l], rmq_[h][r - (1 << h) + 1]);
  }

private:
  std::vector<std::vector<T>> rmq_;
};

class Solution {
public:
  int canCompleteCircuit(const vi& gas, const vi& cost) {
    const auto n = SZ(gas);
    
    vi diff(n), psum(n);
    FOR(i, 0, n-1) {
      diff[i] = gas[i] - cost[i];
      psum[i] = (i == 0) ? diff[i] : diff[i] + psum[i-1];
    }
    
    SparseTable rmq(psum);
    if (rmq.GetMin(0, n-1) >= 0)
      return 0;
    
    auto res = -1;
    FOR(i, 1, n-1) {
      const auto head_sum = psum[i-1];
      const auto tail_sum = psum[n-1] - psum[i-1];

      const auto tail_min = rmq.GetMin(i, n-1) - head_sum;
      const auto head_min = rmq.GetMin(0, i-1);

      if (tail_min >= 0 && head_min + tail_sum >= 0)
        res = i;
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi gas{1,2,3,4,5};
    const vi cost{3,4,5,1,2};
    const auto a_out = Solution().canCompleteCircuit(gas, cost);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi gas{2,3,4};
    const vi cost{3,4,3};
    const auto a_out = Solution().canCompleteCircuit(gas, cost);
    assert(a_out == -1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi gas{3,1,1};
    const vi cost{1,2,2};
    const auto a_out = Solution().canCompleteCircuit(gas, cost);
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
