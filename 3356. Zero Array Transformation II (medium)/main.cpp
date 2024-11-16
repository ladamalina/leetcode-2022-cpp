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

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> diff;

class Solution {
public:
  int minZeroArray(const vi& nums, const vvi& queries) {
    const auto n = SZ(nums), m = SZ(queries);

    const auto check_k = [&](const int k) {
      std::fill(diff.begin(), diff.begin()+n, 0);
      FOR(i, 0, k-1) {
        const auto& q = queries[i];
        const auto l = q[0], r = q[1], d = q[2];
        diff[l] += d;
        if (r+1 < n)
          diff[r+1] -= d;
      }
      FOR(i, 0, n-1) {
        diff[i] += (i > 0) ? diff[i-1] : 0;
        if (diff[i] < nums[i])
          return false;
      }
      return true;
    };
    
    auto lo = 0, hi = m;
    while (lo < hi) {
      const auto mid = (lo + hi) / 2;
      if (check_k(mid))
        hi = mid;
      else
        lo = mid + 1;
    }

    const auto check_lo = check_k(lo);
    return check_lo ? lo : -1;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,0,2};
    const vvi queries{{0,2,1},{0,2,1},{1,1,3}};
    const auto a_out = Solution().minZeroArray(nums, queries);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{4,3,2,1};
    const vvi queries{{1,3,2},{0,2,1}};
    const auto a_out = Solution().minZeroArray(nums, queries);
    assert(a_out == -1);
  
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
