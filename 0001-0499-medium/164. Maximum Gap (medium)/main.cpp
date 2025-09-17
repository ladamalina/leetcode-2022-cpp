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

class Solution {
public:
  int maximumGap(const vi& nums) {
    const auto n = SZ(nums);
    if (n < 2)
      return 0;

    auto x_min = INT_MAX, x_max = INT_MIN;
    for (auto x : nums) {
      x_min = std::min(x_min, x);
      x_max = std::max(x_max, x);
    }

    const auto b_sz = std::max(1, (x_max - x_min) / (n - 1));
    const auto n_bs = (x_max - x_min) / b_sz + 1;
    vvi bs(n_bs);

    for (auto x : nums) {
      const auto idx = (x - x_min) / b_sz;
      bs[idx].push_back(x);
    }

    auto max_gap = 0;
    auto curr_max = 0;
    for (auto& b : bs) {
      if (b.empty())
        continue;
      const auto prev_max = curr_max ? curr_max : b[0];
      auto curr_min = b[0];

      for (auto x : b) {
        curr_max = std::max(curr_max, x);
        curr_min = std::min(curr_min, x);
      }

      max_gap = std::max(max_gap, curr_min - prev_max);
    }

    return max_gap;
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
