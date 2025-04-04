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
using vvl [[maybe_unused]] = std::vector<vl>;
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

constexpr int N_BITS = 31;
constexpr int MAX_N = 1e5;
std::array<std::array<int, MAX_N>, N_BITS> a;

class Solution {
public:
  int longestNiceSubarray(const vi& nums) {
    const auto n = SZ(nums);
    FOR(b, 0, N_BITS-1) {
      auto& ab = a[b];
      FOR(i, 0, n-1) {
        const bool b1 = nums[i] & (1<<b);
        ab[i] = (i == 0) ? b1 : ab[i-1] + b1;
      }
    }

    auto max_len = 1;
    FOR(i, 0, n-2) {
      auto min_i_len = INT_MAX;
      FOR(b, 0, N_BITS-1) {
        const auto& ab = a[b];
        const auto base = (i == 0) ? 0 : ab[i-1];
        auto lo = i, hi = n-1;
        while (lo < hi) {
          const auto mid = (lo + hi + 1) / 2;
          if (ab[mid] - base <= 1)
            lo = mid;
          else
            hi = mid - 1;
        }
        min_i_len = std::min(min_i_len, hi - i + 1);
      }
      max_len = std::max(max_len, min_i_len);
    }

    return max_len;
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
