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

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> a, psum, ssum;

class Solution {
public:
  int minOperations(const vvi& g, const int x) {
    const auto gn = SZ(g), gm = SZ(g[0]);
    auto n = 0;
    FOR(i, 0, gn-1) {
      FOR(j, 0, gm-1) {
        a[n++] = g[i][j];
      }
    }
    std::sort(a.begin(), a.begin() + n);

    FOR(i, 1, n-1) {
      if ((a[i] - a[0]) % x != 0) {
        return -1;
      }
    }

    FOR(i, 0, n-1) {
      psum[i] = (i > 0) ? psum[i-1] + a[i] : a[i];
    }
    FORD(i, n-1, 0) {
      ssum[i] = (i < n-1) ? ssum[i+1] + a[i] : a[i];
    }

    auto min_ops = INT_MAX;
    FOR(i, 0, n-1) { // a[i] - target level
      const auto diff_bef = (i > 0) ? (a[i]*i - psum[i-1]) : 0;
      const auto diff_aft = (i < n-1) ? (ssum[i+1] - a[i]*(n-1-i)) : 0;
      min_ops = std::min(min_ops, (diff_bef + diff_aft) / x);
    }
    return min_ops;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{529,529,989},{989,529,345},{989,805,69}};
    const auto a_out = Solution().minOperations(g, 92);
    assert(a_out == 25);
  
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
