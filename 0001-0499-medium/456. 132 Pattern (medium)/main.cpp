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

template <typename T>
class SparseTable {
public:
  explicit SparseTable(const std::vector<T>& a) {
    const auto n = SZ(a);
    const auto n_bits = 32 - __builtin_clz(n);
    
    rmq_min_ = std::vector<std::vector<T>>(n_bits, std::vector<T>(n));
    rmq_min_[0] = a;
    FOR(h, 1, n_bits-1) {
      FOR(i, 0, n - (1<<h)) {
        rmq_min_[h][i] = std::min(rmq_min_[h-1][i], rmq_min_[h-1][i + (1<<(h-1))]);
      }
    }
    
    rmq_max_ = std::vector<std::vector<T>>(n_bits, std::vector<T>(n));
    rmq_max_[0] = a;
    FOR(h, 1, n_bits-1) {
      FOR(i, 0, n - (1<<h)) {
        rmq_max_[h][i] = std::max(rmq_max_[h-1][i], rmq_max_[h-1][i + (1<<(h-1))]);
      }
    }
  }

  [[nodiscard]] T GetMin(int l, int r) const {
    const auto msb = 31 - __builtin_clz(r - l + 1);
    return std::min(rmq_min_[msb][l], rmq_min_[msb][r - (1<<msb) + 1]);
  }

  [[nodiscard]] T GetMax(int l, int r) const {
    const auto msb = 31 - __builtin_clz(r - l + 1);
    return std::max(rmq_max_[msb][l], rmq_max_[msb][r - (1<<msb) + 1]);
  }

private:
  std::vector<std::vector<T>> rmq_min_;
  std::vector<std::vector<T>> rmq_max_;
};

class Solution {
public:
  bool find132pattern(const vi& nums) {
    SparseTable<int> rmq(nums);
    const auto n = SZ(nums);
    FOR(i, 2, n-1) {
      if (rmq.GetMin(0, i-1) < nums[i] && nums[i] < rmq.GetMax(0, n-1)) {
        int lo = 0, hi = i-1;
        while (lo < hi) {
          const auto mid = (lo + hi) / 2;
          if (rmq.GetMin(0, mid) < nums[i])
            hi = mid;
          else
            lo = mid + 1;
        }
        if (lo < i - 1 && nums[i] < rmq.GetMax(lo + 1, i - 1))
          return true;
      }
    }
    return false;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
