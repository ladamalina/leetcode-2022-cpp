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

class SparseTableGCD {
public:
  explicit SparseTableGCD(const vi& a) {
    const auto n = SZ(a);
    const auto n_bits = 32 - __builtin_clz(n);
    rmq_gcd_ = vvi(n_bits, vi(n));
    rmq_gcd_[0] = a;
    for (auto h = 1; h < n_bits; ++h) {
      for (auto i = 0; i <= n - (1<<h); ++i) {
        rmq_gcd_[h][i] = std::gcd(rmq_gcd_[h-1][i], rmq_gcd_[h-1][i + (1 << (h-1))]);
      }
    }
  }
  [[nodiscard]] int GetGCD(const int l, const int r) const {
    const auto msb = 31 - __builtin_clz(r - l + 1);
    return std::gcd(rmq_gcd_[msb][l], rmq_gcd_[msb][r - (1 << msb) + 1]);
  }
private:
  vvi rmq_gcd_;
};

class Solution {
public:
  int minOperations(const vi& nums) {
    const auto n = SZ(nums);
    const auto c1 = CI(std::count(RNG(nums), 1));
    if (c1) return n - c1;
    
    const SparseTableGCD t(nums);

    auto min_len = n + 1;
    FOR(l, 0, n-1) {
      FOR(r, l, n-1) {
        const auto g = t.GetGCD(l, r);
        if (g == 1)
          min_len = std::min(min_len, r - l + 1);
      }
    }

    if (min_len > n) return -1;
    return (min_len - 1) + (n - 1);
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
